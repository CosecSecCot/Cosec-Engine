#ifndef TextureManager_hpp
#define TextureManager_hpp
#pragma once

#include "Game.hpp"
#include "SDL_image.h"

#include <cassert>
#include <stdexcept>
#include <string>

class TextureManager {
public:
    static SDL_Texture *loadTexture(const std::string &filename, SDL_Rect *rect) {
        assert(Game::renderer != nullptr && "Renderer cannot be null");

        SDL_Surface *tempSurface = IMG_Load(filename.c_str());
        if (tempSurface == nullptr) {
            throw std::runtime_error("Failed to load image: " + filename + "\n" + std::string(IMG_GetError()));
        }

        rect->w = tempSurface->w;
        rect->h = tempSurface->h;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        if (texture == nullptr) {
            throw std::runtime_error("Failed to create texture from surface\n" + std::string(SDL_GetError()));
        }

        SDL_FreeSurface(tempSurface);

        return texture;
    }

    static SDL_Texture *loadTexture(const std::string &filename) {
        assert(Game::renderer != nullptr && "Renderer cannot be null");

        SDL_Surface *tempSurface = IMG_Load(filename.c_str());
        if (tempSurface == nullptr) {
            throw std::runtime_error("Failed to load image: " + filename + "\n" + std::string(IMG_GetError()));
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        if (texture == nullptr) {
            throw std::runtime_error("Failed to create texture from surface\n" + std::string(SDL_GetError()));
        }

        SDL_FreeSurface(tempSurface);

        return texture;
    }
};

#endif /* TextureManager.hpp */
