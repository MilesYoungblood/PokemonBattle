//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

bool Map::isTrainerHere(const int x, const int y) const {
    for (const std::unique_ptr<Trainer> &trainer : this->trainers) {
        if (trainer->getX() == x and trainer->getY() == y) {
            return true;
        }
    }
    return false;
}

Map::Map(const char *name, const char *music, int width, int height)
        : name(name), music(music), width(width), height(height) {
    // initialize the layout with grass
    this->layout.resize(this->width);
    for (int i = 0; i < this->width; ++i) {
        this->layout[i].resize(this->height);

        for (int j = 0; j < this->height; ++j) {
            this->layout[i][j] = { Map::Tile::ID::GRASS, i * TILE_SIZE, j * TILE_SIZE };
        }
    }

    // set the top border
    for (int i = 0; i < 3; ++i) {
        for (int x = 0; x < this->width; ++x) {
            this->layout[x][i].id = Map::Tile::ID::OBSTRUCTION;
        }
    }

    // set the inner layer borders
    for (int i = 0; i < 4; ++i) {
        for (int y = 1; y < this->height; ++y) {
            this->layout[i][y].id = Map::Tile::ID::OBSTRUCTION;
            this->layout[this->width - 1 - i][y].id = Map::Tile::ID::OBSTRUCTION;
        }
    }

    // set the bottom border
    for (int i = 0; i < 3; ++i) {
        for (int x = 0; x < this->width; ++x) {
            this->layout[x][this->height - 1 - i].id = Map::Tile::ID::OBSTRUCTION;
        }
    }
}

Map &Map::operator=(Map &&toMove) noexcept {
    this->name = toMove.name;
    this->music = toMove.music;
    this->width = toMove.width;
    this->height = toMove.height;
    this->layout = std::move(toMove.layout);
    this->trainers = std::move(toMove.trainers);
    this->items = std::move(toMove.items);
    this->exitPoints = std::move(toMove.exitPoints);

    return *this;
}

Map::~Map() {
    SDL_DestroyTexture(Map::obstruction);
    SDL_DestroyTexture(Map::grass);
    SDL_DestroyTexture(Map::tallGrass);
}

void Map::initTextures() {
    static bool isInitialized = false;
    // only allow calls to this function if the TextureManager is initialized,
    // and if Maps are not already initialized
    if (not isInitialized and TextureManager::getInstance()) {
        Map::obstruction = TextureManager::getInstance().loadTexture(PROJECT_PATH + R"(\sprites\textures\tree.png)");
        Map::grass = TextureManager::getInstance().loadTexture(PROJECT_PATH + R"(\sprites\textures\grass.png)");

        isInitialized = true;
    }
}

// returns true if an obstruction is at the passed coordinates
bool Map::isObstructionHere(const int x, const int y) const {
    // out of bounds or an NPC is already in this spot
    if ((x < 0 or this->width - 1 < x) or (y < 0 or this->height - 1 < y) or this->isTrainerHere(x, y)) {
        return true;
    }

    return this->layout[x][y].id == Map::Tile::ID::OBSTRUCTION;
}

void Map::addExitPoint(const ExitPoint &exitPoint) {
    this->exitPoints.push_back(exitPoint);
    this->layout[exitPoint.x][exitPoint.y].id = Map::Tile::ID::GRASS;
}

// returns an array with the new x and y coordinates and the new map respectively,
// if no exit point is here, returns filler coordinates with the third element being -1
std::array<int, 3> Map::isExitPointHere(const int x, const int y) const {
    for (const ExitPoint &exit_point : this->exitPoints) {
        if (exit_point.x == x and exit_point.y == y) {
            return { exit_point.newX, exit_point.newY, exit_point.newMap };
        }
    }
    return { 0, 0, -1 };
}

void Map::addTrainer(std::unique_ptr<Trainer> toAdd) {
    this->trainers.push_back(std::move(toAdd));
}

// returns the number of NPCs
int Map::numTrainers() const {
    return static_cast<int>(this->trainers.size());
}

// returns the trainer at the passed index
Trainer &Map::operator[](const int index) {
    return *this->trainers[index];
}

const Trainer &Map::operator[](const int index) const {
    return *this->trainers[index];
}

const char *Map::getMusic() const {
    return this->music;
}

// places an obstruction at the passed coordinates
void Map::setObstruction(const int x, const int y) {
    if (not this->isTrainerHere(x, y)) {
        this->layout[x][y].id = Map::Tile::ID::OBSTRUCTION;
    }
}

// shift the map and its trainers, according to a passed in flag
void Map::shift(Direction direction, int distance) {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            switch (direction) {
                case Direction::DOWN:
                    this->layout[row][column].y += distance;
                    break;
                case Direction::UP:
                    this->layout[row][column].y -= distance;
                    break;
                case Direction::RIGHT:
                    this->layout[row][column].x += distance;
                    break;
                case Direction::LEFT:
                    this->layout[row][column].x -= distance;
                    break;
                default:
                    return;
            }
        }
    }

    for (const std::unique_ptr<Trainer> &trainer : this->trainers) {
        switch (direction) {
            case Direction::DOWN:
                trainer->shiftDownOnMap(distance);
                break;
            case Direction::UP:
                trainer->shiftUpOnMap(distance);
                break;
            case Direction::RIGHT:
                trainer->shiftRightOnMap(distance);
                break;
            case Direction::LEFT:
                trainer->shiftLeftOnMap(distance);
                break;
            default:
                return;
        }
    }
}

void Map::render() {
    SDL_Rect sdlRect;
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            sdlRect = { this->layout[row][column].x, this->layout[row][column].y, TILE_SIZE, TILE_SIZE };
            // prevents rendering tiles that aren't onscreen
            if (Camera::getInstance().isInView(sdlRect) != 0U) {
                switch (this->layout[row][column].id) {
                    case Map::Tile::ID::GRASS:
                        TextureManager::getInstance().draw(Map::grass, sdlRect);
                        break;

                    case Map::Tile::ID::TALL_GRASS:
                        TextureManager::getInstance().draw(Map::tallGrass, sdlRect);
                        break;

                    case Map::Tile::ID::OBSTRUCTION:
                        TextureManager::getInstance().draw(Map::grass, sdlRect);
                        TextureManager::getInstance().draw(Map::obstruction, sdlRect);
                        break;

                    case Map::Tile::ID::WATER:
                        Map::water.update();
                        Map::water.render(sdlRect);
                        break;

                    default:
                        break;
                }
            }
        }
    }

    for (const std::unique_ptr<Trainer> &trainer : this->trainers) {
        // prevents rendering trainers that aren't onscreen
        if (Camera::getInstance().isInView({ trainer->getScreenX(), trainer->getScreenY(), TILE_SIZE, TILE_SIZE }) != 0U) {
            trainer->render();
        }
    }
}

// resets the previous map's tile positions
// as well as the trainer's positions
void Map::reset() {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            this->layout[row][column] = { this->layout[row][column].id, row * TILE_SIZE, column * TILE_SIZE };
        }
    }

    for (auto &trainer : this->trainers) {
        trainer->resetPos();
    }
}

bool Entity::canMoveForward(const Map *map) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return not map->isObstructionHere(this->x, this->y - 1);
        case Direction::RIGHT:
            return not map->isObstructionHere(this->x + 1, this->y);
        case Direction::DOWN:
            return not map->isObstructionHere(this->x, this->y + 1);
        case Direction::LEFT:
            return not map->isObstructionHere(this->x - 1, this->y);
        default:
            throw std::runtime_error("Unexpected error: function canMoveForward");
    }
}
