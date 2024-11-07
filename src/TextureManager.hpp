#ifndef TextureManager_hpp
#define TextureManager_hpp
#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <cassert>
#include <stdexcept>
#include <string>

class TextureManager {
public:
    static SDL_Texture *loadTexture(const char *filename, SDL_Rect *rect, SDL_Renderer *renderer) {
        assert(renderer != nullptr && "Renderer cannot be null");

        SDL_Surface *tempSurface = IMG_Load(filename);
        if (tempSurface == nullptr) {
            throw std::runtime_error("Failed to load image: " + std::string(filename) + "\n" +
                                     std::string(IMG_GetError()));
        }

        rect->w = tempSurface->w;
        rect->h = tempSurface->h;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if (texture == nullptr) {
            throw std::runtime_error("Failed to create texture from surface\n" + std::string(SDL_GetError()));
        }

        SDL_FreeSurface(tempSurface);

        return texture;
    }

    static SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer) {
        assert(renderer != nullptr && "Renderer cannot be null");

        SDL_Surface *tempSurface = IMG_Load(filename);
        if (tempSurface == nullptr) {
            throw std::runtime_error("Failed to load image: " + std::string(filename) + "\n" +
                                     std::string(IMG_GetError()));
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if (texture == nullptr) {
            throw std::runtime_error("Failed to create texture from surface\n" + std::string(SDL_GetError()));
        }

        SDL_FreeSurface(tempSurface);

        return texture;
    }
};

#endif /* TextureManager.hpp */
