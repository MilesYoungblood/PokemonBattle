//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

// responsible for creating textures and drawing to the renderer
class TextureManager {
private:
    SDL_Renderer *textureRenderer{ nullptr };

    bool isInitialized{ false };

    TextureManager() = default;

public:
    static TextureManager &getInstance() {
        static TextureManager textureManager;
        return textureManager;
    }

    void init(SDL_Renderer *renderer) {
        // only allow this function to be called once per instantiation of TextureManager object
        if (this->isInitialized) {
            return;
        }
        this->textureRenderer = renderer;
        this->isInitialized = true;
    }

    SDL_Texture *loadTexture(std::string_view path) {
        return IMG_LoadTexture(this->textureRenderer, path.data());
    }

    SDL_Texture *loadText(TTF_Font *font, const char *text, SDL_Color fg) {
        SDL_Surface *temp = TTF_RenderText_Solid(font, text, fg);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
        SDL_FreeSurface(temp);

        return texture;
    }

    SDL_Texture *loadText(TTF_Font *font, std::string_view text, SDL_Color fg) {
        SDL_Surface *temp = TTF_RenderText_Solid(font, text.data(), fg);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
        SDL_FreeSurface(temp);

        return texture;
    }

    void draw(SDL_Texture *texture, const SDL_Rect &dest) {
        SDL_RenderCopy(this->textureRenderer, texture, nullptr, &dest);
    }

    void drawFrame(SDL_Texture *texture, const SDL_Rect &dest, int frame, int row) {
        const SDL_Rect src{ dest.w * frame, dest.h * row, dest.w, dest.h };
        SDL_RenderCopy(this->textureRenderer, texture, &src, &dest);
    }

    void drawRectWithOutline(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize) {
        // draw the inner box
        SDL_SetRenderDrawColor(this->textureRenderer, fg.r, fg.g, fg.b, fg.a);
        SDL_RenderFillRect(this->textureRenderer, &dest);

        SDL_Rect border{ dest.x - 1, dest.y - 1, dest.w + 2, dest.h + 2 };

        // draw the border
        SDL_SetRenderDrawColor(this->textureRenderer, bg.r, bg.g, bg.b, bg.a);
        for (int i = 0; i < borderSize; ++i) {
            SDL_RenderDrawRect(this->textureRenderer, &border);
            --border.x;
            --border.y;
            border.w += 2;
            border.h += 2;
        }
    }

    explicit operator bool() const {
        return this->isInitialized;
    }
};
