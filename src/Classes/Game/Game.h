//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include "../../Classes/Map/Map.h"
#include "../../Classes/Player/Player.h"
#include "../../Classes/Factory/PokemonFactory.h"
#include "../../Classes/Factory/MoveFactory.h"

class Game {
private:
    static void saveData();
    static void loadData();
    static void eraseData();

public:
    Game();
    Game(const Game &) = delete;
    Game& operator=(const Game &) = delete;

    static void handleEvents();
    static void update();
    static void render();
    static void clean();

    explicit operator bool() const;
};
