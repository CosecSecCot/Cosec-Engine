#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "SDL_render.h"
#include "TextureManager.hpp"

class TextureComponent : public Component {
public:
    TextureComponent() = delete;
    TextureComponent(const std::string &path, TransformComponent &transform) : transform(&transform) {
        assert(this->transform != nullptr && "TransformComponent cannot be null!");

        this->texture = TextureManager::loadTexture(path);

        // TODO: Change it to actual width and height of texture
        this->srcRect.x = 0;
        this->srcRect.y = 0;
        this->srcRect.w = 24;
        this->srcRect.h = 24;

        this->destRect.x = static_cast<int>(this->transform->position.x);
        this->destRect.y = static_cast<int>(this->transform->position.y);
        this->destRect.w = srcRect.w * 2;
        this->destRect.h = srcRect.h * 2;
    }

    void update() override {
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
    SDL_Rect srcRect, destRect;
};
