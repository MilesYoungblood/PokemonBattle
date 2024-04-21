//
// Created by Miles on 10/2/2023.
//

#include "../TextureManager/TextureManager.h"
#include "../Mixer/Mixer.h"
#include "Game.h"

Game::~Game() {
    Mix_HaltMusic();
    Mix_HookMusicFinished(nullptr);
    Mix_CloseAudio();

    Scene::getInstance<Overworld>().clean();
    TextureManager::getInstance().clean();
    TTF_Quit();

    IMG_Quit();

    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Unable to destroy renderer: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Unable to destroy window: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
    SDL_Quit();
}

void Game::handleEvents() const {
    this->currentScene->handleEvents();
}

void Game::update() {
    if (currentScene->getState(Scene::State::FADING_IN)) {
        this->currentScene->fadeIn();

        if (this->currentScene->getState(Scene::State::FADED_IN)) {
            this->currentScene->setState(Scene::State::RUNNING);
        }
    }

    this->currentScene->update();

    if (currentScene->getState(Scene::State::FADING_OUT)) {
        this->currentScene->fadeOut();

        if (this->currentScene->getState(Scene::State::FADED_OUT)) {
            this->currentScene = this->scenes.at(static_cast<std::size_t>(*this->nextScene));
            this->nextScene.reset(nullptr);

            this->currentScene->init();
            this->currentScene->setState(Scene::State::FADING_IN);
        }
    }
}

void Game::render() const {
    SDL_RenderClear(this->renderer);
    this->currentScene->render();
    TextureManager::getInstance().drawScreen();
    SDL_RenderPresent(this->renderer);
}

void Game::terminate() {
    this->running = false;
}

int Game::getFps() const {
    return this->currentFps;
}

bool Game::isRunning() const {
    return this->running;
}

void Game::setRenderColor(const SDL_Color color) const {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Game::changeScene(Scene::Id x) {
    this->nextScene = std::make_unique<Scene::Id>(x);
    this->currentScene->setState(Scene::State::FADING_OUT);
}

Game::Game() {
    // initialize subsystems
    if (SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::clog << "Error initializing subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // create window
    this->window = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (this->window == nullptr) {
        std::clog << "Error creating window: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // initialize image subsystems
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::clog << "Error initializing image subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load window icon
    SDL_Surface *pokeball = IMG_Load("../assets/images/pokeball.png");
    if (pokeball == nullptr) {
        std::clog << "Error loading icon: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // set the window icon
    SDL_SetWindowIcon(this->window, pokeball);
    SDL_FreeSurface(pokeball);

    // create renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if (this->renderer == nullptr) {
        std::clog << "Error creating renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // initialize true type font subsystems
    if (TTF_Init() == -1) {
        std::clog << "Error initializing TTF subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // initialize TextureManager
    if (not TextureManager::getInstance().init(this->renderer)) {
        return;
    }

    // initialize audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
        std::clog << "Error opening the default audio device: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    Mixer::getInstance().playMusic("TitleScreen");

    this->running = true;
}