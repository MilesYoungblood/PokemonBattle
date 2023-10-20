#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"


#define SDL_MAIN_HANDLED

#include "Classes/Game/Game.h"

constexpr int FPS = 30;
constexpr int FRAME_DELAY = 1000 / FPS;

auto main() -> int {
    SDL_SetMainReady();

    Uint32 frameStart;
    Uint32 frameTime;

    Game game;

    while (game) {
        frameStart = SDL_GetTicks();

        Game::handleEvents();
        Game::update();
        Game::render();

        frameTime = SDL_GetTicks() - frameStart;

        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 0;
}


#pragma clang diagnostic pop
