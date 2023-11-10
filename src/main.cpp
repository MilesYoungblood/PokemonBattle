#pragma clang diagnostic add
#pragma ide diagnostic ignored "OCUnusedMacroInspection"


#define SDL_MAIN_HANDLED

#include "Classes/Game/Game.h"

int main() {
    SDL_SetMainReady();

    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 frameDelay;

    Game::getInstance();

    while (Game::getInstance()) {
        frameStart = SDL_GetTicks64();

        Game::getInstance().handleEvents();
        Game::getInstance().update();
        Game::getInstance().render();

        frameTime = SDL_GetTicks64() - frameStart;
        frameDelay = 1000 / Game::getFPS();

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}


#pragma clang diagnostic pop
