#include "GameObject.hpp"
#include "TextureManager.hpp"

#define UPSCALE_FACTOR 2
#define SIZE_IN_PX 24

GameObject::GameObject(const char *textureSheet, int x, int y) : xPosition(x), yPosition(y) {

    this->texture = TextureManager::loadTexture(textureSheet);

    this->srcRect.x = 0;
    this->srcRect.y = 0;
    this->srcRect.w = SIZE_IN_PX;
    this->srcRect.h = SIZE_IN_PX;

    this->destRect.w = srcRect.w * UPSCALE_FACTOR;
    this->destRect.h = srcRect.h * UPSCALE_FACTOR;
}

GameObject::~GameObject() {
    SDL_DestroyTexture(this->texture);
}

void GameObject::update() {
    xPosition++;
    yPosition++;

    this->destRect.x = xPosition;
    this->destRect.y = yPosition;
}

void GameObject::render() {
    assert(Game::renderer != nullptr && "Renderer cannot be null.");

    SDL_RenderCopy(Game::renderer, this->texture, &this->srcRect, &this->destRect);
}
