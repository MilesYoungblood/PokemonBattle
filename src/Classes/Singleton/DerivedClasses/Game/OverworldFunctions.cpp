//
// Created by Miles Youngblood on 10/24/2023.
//

#include "Game.h"

int walkCounter = 0;                                     // measures how many screen pixels the player has moved

bool keepMovingForward = false;                          // ultimately, determine when the player stops moving
bool momentum = false;                                   // denotes whether the player is still moving

void Game::changeMap(const std::tuple<int, int, Map::Id> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        this->isRunning = false;
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mix_FreeMusic(Game::getInstance().music);

        Game::getInstance().music = Mix_LoadMUS(std::string_view(
                "../assets/audio/music/" + Game::getInstance().currentMap->getMusic() + ".mp3").data());
        if (Game::getInstance().music == nullptr) {
            std::clog << "Error loading \"" << Game::getInstance().currentMap->getMusic() << "\": " << SDL_GetError()
                      << '\n';
            SDL_ClearError();
            Game::getInstance().isRunning = false;
            return;
        }

        if (Mix_PlayMusic(Game::getInstance().music, -1) == -1) {
            std::clog << "Error playing \"" << Game::getInstance().currentMap->getMusic() << "\": " << SDL_GetError()
                      << '\n';
            SDL_ClearError();
            Game::getInstance().isRunning = false;
            return;
        }
    });

    this->currentMap->reset();

    // move the new map into the current map variable
    this->currentMapIndex = std::get<2>(data);
    this->currentMap = &this->maps.at(this->currentMapIndex);

    // resets the states of these variables for each trainer
    std::for_each(this->currentMap->begin(), this->currentMap->end(), [](std::unique_ptr<Trainer> &trainer) -> void {
        pixelsTraveled[&trainer] = 0;
        keepLooping[&trainer] = true;
    });

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer(Game::getInstance().currentMap);
}

void Game::createTextBox(const std::vector<std::string> &messages) const {
    GraphicsEngine::getInstance().addGraphic<TextBox>(TextBox::getInstance());
    GraphicsEngine::getInstance().getGraphic<TextBox>().setFinishedCallback([] -> void {
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    });

    const int box_width = Constants::TILE_SIZE * 7;
    const int box_height = Constants::TILE_SIZE * 2;
    const SDL_Rect rect{
            this->WINDOW_WIDTH / 2 - box_width / 2,
            this->WINDOW_HEIGHT - box_height,
            box_width,
            box_height - Constants::TILE_SIZE / 2
    };
    GraphicsEngine::getInstance().getGraphic<TextBox>().init(rect, rect.h / (Constants::TILE_SIZE * 3 / 10),
                                                             rect.x + Constants::TILE_SIZE / 10,
                                                             rect.y + Constants::TILE_SIZE / 10);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(messages);
}

void Game::checkForOpponents() {
    static void (*resetVariables)() = [] -> void {
        momentum = false;
        keepMovingForward = false;
        walkCounter = 0;
    };

    // resets movement variables if you are not inputting any directions
    if (not(KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D))) {
        resetVariables();
    }

    static int frameCounter = 0;    // makes a trainer that spotted the player stand still for a set number of frames
    static bool haltMusic = true;
    static bool freeMusic = true;

    // checks if the player is in LoS for any trainer
    for (auto &trainer : *this->currentMap) {
        if (trainer->canFight() and keepLooping[&trainer] and trainer->hasVisionOf(&Player::getPlayer())) {
            if (haltMusic) {
                Mix_HaltMusic();
                haltMusic = false;
            }
            KeyManager::getInstance().blockInput();
            resetVariables();
            trainer->lock();

            ++frameCounter;
            if (frameCounter < 50 * (this->currentFps / 30)) {
                return;
            }

            if (freeMusic) {
                Mix_FreeMusic(this->music);

                this->music = Mix_LoadMUS("../assets/audio/music/GymBattle.mp3");
                if (this->music == nullptr) {
                    std::clog << "Error loading \"GymBattle\": " << SDL_GetError() << '\n';
                    SDL_ClearError();
                    this->isRunning = false;
                    return;
                }

                if (Mix_PlayMusic(this->music, -1) == -1) {
                    std::clog << "Error playing \"GymBattle\": " << SDL_GetError() << '\n';
                    SDL_ClearError();
                    this->isRunning = false;
                    return;
                }

                freeMusic = false;
            }

            if (not trainer->isNextTo(&Player::getPlayer())) {
                trainer->shiftDirectionOnMap(trainer->getDirection(), this->SCROLL_SPEED);
                pixelsTraveled[&trainer] += this->SCROLL_SPEED;

                if (pixelsTraveled[&trainer] % (Constants::TILE_SIZE / 2) == 0) {
                    trainer->updateAnimation();
                }

                if (pixelsTraveled[&trainer] % Constants::TILE_SIZE == 0) {
                    trainer->moveForward();
                }
            }
            else {
                Player::getPlayer().face(trainer.get());

                this->createTextBox(trainer->getDialogue());

                keepLooping[&trainer] = false;

                frameCounter = 0;
                haltMusic = true;
                freeMusic = true;
            }
            break;
        }
    }
}

void Game::updateOverworld() {
    static auto checkKey = [this](SDL_Scancode scancode) -> void {
        static auto directionAsKey = [](SDL_Scancode key) -> Direction {
            switch (key) {
                case SDL_Scancode::SDL_SCANCODE_W:
                    return Direction::UP;
                case SDL_Scancode::SDL_SCANCODE_A:
                    return Direction::LEFT;
                case SDL_Scancode::SDL_SCANCODE_S:
                    return Direction::DOWN;
                case SDL_Scancode::SDL_SCANCODE_D:
                    return Direction::RIGHT;
                default:
                    throw std::invalid_argument("Scancode passed does not correspond to a direction");
            }
        };

        if (not Player::getPlayer().isFacing(directionAsKey(scancode))) {
            Player::getPlayer().setDirection(directionAsKey(scancode));
        }
        if (KeyManager::getInstance().getKey(scancode) and Player::getPlayer().canMoveForward(this->currentMap) and
            (momentum or keyDelay >= 10)) {
            KeyManager::getInstance().lockWasd();
            keepMovingForward = true;

            momentum = true;
            keyDelay.stop();
            keyDelay.reset();
        }
    };

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
        checkKey(SDL_Scancode::SDL_SCANCODE_W);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
        checkKey(SDL_Scancode::SDL_SCANCODE_A);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
        checkKey(SDL_Scancode::SDL_SCANCODE_S);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
        checkKey(SDL_Scancode::SDL_SCANCODE_D);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN) and not keepMovingForward) {
        for (auto &trainer : *this->currentMap) {
            if (Player::getPlayer().hasVisionOf(trainer.get())) {
                // if the player manually clicked Enter
                if (GraphicsEngine::getInstance().hasAny<TextBox>()) {
                    trainer->face(&Player::getPlayer());
                    trainer->lock();
                    KeyManager::getInstance().blockInput();

                    // only create the textbox here if the trainer cannot fight;
                    // the program will loop back to checkForOpponents()
                    // and create it there if the trainer can fight
                    if (not trainer->canFight()) {
                        this->createTextBox(trainer->getDialogue());
                    }
                }
                else {
                    // if the textbox still has messages to print
                    if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                        KeyManager::getInstance().blockInput();
                        GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

                        if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                            SoundPlayer::getInstance().playSound("accept");
                        }
                    }
                    // if the textbox is done printing
                    if (GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                        GraphicsEngine::getInstance().removeGraphic<TextBox>();
                        // re-lock the Enter key
                        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

                        // sets a cool-down period before the Enter key can be registered again;
                        // this is needed because the program will register a button as
                        // being pressed faster than the user can lift their finger
                        std::thread coolDown([] -> void {
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
                        });
                        coolDown.detach();
                        KeyManager::getInstance().unlockWasd();

                        if (trainer->canFight()) {
                            Mix_FreeMusic(this->music);

                            this->music = Mix_LoadMUS("../assets/audio/music/TrainerBattle.mp3");
                            if (this->music == nullptr) {
                                std::clog << "Error loading \"TrainerBattle\": " << SDL_GetError() << '\n';
                                SDL_ClearError();
                                this->isRunning = false;
                                return;
                            }

                            if (Mix_PlayMusic(this->music, -1) == -1) {
                                std::clog << "Error playing \"TrainerBattle\": " << SDL_GetError() << '\n';
                                SDL_ClearError();
                                this->isRunning = false;
                                return;
                            }

                            this->currentState = Game::State::BATTLE;
                            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                        }
                        else {
                            trainer->unlock();
                        }
                    }

                    keyDelay.reset();
                    break;
                }
            }
        }
    }

    if (keepMovingForward) {
        if (walkCounter % (Constants::TILE_SIZE / 2) == 0) {
            Player::getPlayer().updateAnimation();
        }
        if (walkCounter % Constants::TILE_SIZE == 0) {
            Player::getPlayer().moveForward();
        }

        this->currentMap->shift(oppositeDirection(Player::getPlayer().getDirection()), this->SCROLL_SPEED);
        walkCounter += this->SCROLL_SPEED;
    }

    // if the player's sprite is on a tile...
    if (walkCounter % Constants::TILE_SIZE == 0) {
        if (GraphicsEngine::getInstance().hasAny<TextBox>()) {
            KeyManager::getInstance().unlockWasd();
        }

        keepMovingForward = false;

        checkForOpponents();
        const auto map_data = this->currentMap->isExitPointHere(Player::getPlayer().getX(), Player::getPlayer().getY());
        if (map_data.has_value()) {
            this->changeMap(map_data.value());
        }
    }

    for (auto &trainer : *this->currentMap) {
        trainer->act();
    }

    GraphicsEngine::getInstance().update();
}

void Game::renderOverworld() {
    this->currentMap->render();
    Player::getPlayer().render();

    GraphicsEngine::getInstance().render();
}