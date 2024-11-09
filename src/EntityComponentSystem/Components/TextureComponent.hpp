#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/PositionComponent.hpp"
#include "SDL_render.h"
#include "TextureManager.hpp"

class TextureComponent : public Component {
public:
    TextureComponent() = delete;
    TextureComponent(const std::string &path, PositionComponent &pos) : positionComponent(&pos) {
        assert(this->positionComponent != nullptr && "PositionComponent cannot be nullptr!");

        this->texture = TextureManager::loadTexture(path);

        // TODO: Change it to actual width and height of texture
        this->srcRect.x = 0;
        this->srcRect.y = 0;
        this->srcRect.w = 24;
        this->srcRect.h = 24;

        this->destRect.x = positionComponent->x();
        this->destRect.y = positionComponent->y();
        this->destRect.w = srcRect.w * 2;
        this->destRect.h = srcRect.h * 2;
    }

    void update() override {
        this->destRect.x = positionComponent->x();
        this->destRect.y = positionComponent->y();
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
    PositionComponent *positionComponent;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};
