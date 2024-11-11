#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "SDL_render.h"
#include "TextureManager.hpp"

class TextureComponent : public Component {
public:
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
    }

    explicit TextureComponent(const std::string &path, TransformComponent &transform, int srcX, int srcY)
        : TextureComponent(path, transform) {
        this->srcRect.x = srcX;
        this->srcRect.y = srcY;
    }

    ~TextureComponent() override {
        SDL_DestroyTexture(this->texture);
    }

    void update() override {
        // Lets say we adjusted the scale during a frame
        // then texture's size should also change
        this->destRect.w = srcRect.w * this->transform->scale;
        this->destRect.h = srcRect.h * this->transform->scale;

        this->destRect.x = static_cast<int>(transform->position.x);
        this->destRect.y = static_cast<int>(transform->position.y);
    }

    void render() {
        assert(Game::renderer != nullptr && "Renderer cannot be null.");

        SDL_RenderCopy(Game::renderer, this->texture, &this->srcRect, &this->destRect);
    }

    void setSrcX(int x) {
        this->srcRect.x = x;
    }

    void setSrcY(int y) {
        this->srcRect.y = y;
    }

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect{}, destRect{};
};
