#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "SDL_render.h"
#include "TextureManager.hpp"

class TextureComponent : public Component {
public:
    Vector2D pivotOffset{0.5, 0.5};
    Vector2D pivot;
    SDL_Rect srcRect{}, destRect{};

    TextureComponent() = delete;

    explicit TextureComponent(const std::string &path, TransformComponent &transform) : transform(&transform) {
        assert(this->transform != nullptr && "TransformComponent cannot be null!");

        this->texture = TextureManager::loadTexture(path);

        this->srcRect.x = 0;
        this->srcRect.y = 0;
        this->srcRect.w = this->transform->width;
        this->srcRect.h = this->transform->height;

        this->destRect.x = static_cast<int>(this->transform->position.x);
        this->destRect.y = static_cast<int>(this->transform->position.y);
        this->destRect.w = srcRect.w * this->transform->scale;
        this->destRect.h = srcRect.h * this->transform->scale;

        this->pivot = {(float)this->destRect.x + ((float)this->destRect.w * pivotOffset.x),
                       (float)this->destRect.y + ((float)this->destRect.h * pivotOffset.y)};
    }

    explicit TextureComponent(const std::string &path, TransformComponent &transform, int srcX, int srcY)
        : TextureComponent(path, transform) {
        this->srcRect.x = srcX;
        this->srcRect.y = srcY;
    }

    explicit TextureComponent(const std::string &path, TransformComponent &transform, int srcX, int srcY,
                              Vector2D pivot)
        : TextureComponent(path, transform, srcX, srcY) {
        this->pivotOffset = pivot;
        this->pivot = {(float)this->destRect.x + ((float)this->destRect.w * pivotOffset.x),
                       (float)this->destRect.y + ((float)this->destRect.h * pivotOffset.y)};
    }

    ~TextureComponent() override {
        SDL_DestroyTexture(this->texture);
    }

    void flipHorizontal() {
        this->flip = SDL_FLIP_HORIZONTAL;
    }

    void flipVertical() {
        this->flip = SDL_FLIP_VERTICAL;
    }

    void flipReset() {
        this->flip = SDL_FLIP_NONE;
    }

    void update() override {
        // Lets say we adjusted the scale during a frame
        // then texture's size should also change
        this->destRect.w = srcRect.w * this->transform->scale;
        this->destRect.h = srcRect.h * this->transform->scale;

        this->destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        this->destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

        this->pivot = {(float)this->destRect.x + ((float)this->destRect.w * pivotOffset.x),
                       (float)this->destRect.y + ((float)this->destRect.h * pivotOffset.y)};
    }

    void render() {
        assert(Game::renderer != nullptr && "Renderer cannot be null.");

        SDL_RenderCopyEx(Game::renderer, this->texture, &this->srcRect, &this->destRect, 0.0, nullptr, flip);
    }

    void debug() const {
        assert(Game::renderer != nullptr && "Renderer cannot be null.");
        if (!Game::renderDebug)
            return;

        SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(Game::renderer, &this->destRect);
        SDL_RenderDrawPoint(Game::renderer, static_cast<int>(pivot.x), static_cast<int>(pivot.y));
    }

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};
