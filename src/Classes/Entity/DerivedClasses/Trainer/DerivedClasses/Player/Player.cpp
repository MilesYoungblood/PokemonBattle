//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player *Player::instancePtr = nullptr;
std::array<std::array<Pokemon *, 30>, 12> Player::pc;

Player::Player(int x, int y, int direction) : Trainer(x, y) {
    this->setFrontModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_front.png)"));
    this->setBackModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_back.png)"));
    this->setLeftModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_left.png)"));
    this->setRightModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_right.png)"));

    this->setDirection(static_cast<Direction>(direction));

    std::cout << "Player created!\n\n";
}

Player * Player::getPlayer(int x, int y, int direction) {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player(x, y, direction);
    }
    return Player::instancePtr;
}

void Player::destroyPlayer() {
    delete Player::instancePtr;
    Player::instancePtr = nullptr;
}

void Player::addToPC(Pokemon *toAdd) {
    for (auto &box : Player::pc) {
        for (auto &pokemon : box) {
            if (pokemon == nullptr) {
                pokemon = toAdd;
            }
        }
    }
}

Player::operator bool() const {
    return this->getFaintCount() < this->partySize();
}

bool Player::canFight() const {
    return this->getFaintCount() < this->partySize();
}
