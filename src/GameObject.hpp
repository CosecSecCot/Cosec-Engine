#ifndef GameObject_hpp
#define GameObject_hpp
#pragma once

#include "SDL.h"

class GameObject {
public:
    GameObject(const char *textureSheet, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    int xPosition, yPosition;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};

#endif /* GameObject.hpp */
