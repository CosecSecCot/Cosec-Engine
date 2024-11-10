#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "Game.hpp"

#include <cassert>

class ColliderComponent : public Component {
public:
    SDL_Rect collider{};

    explicit ColliderComponent(TransformComponent &transform) : transform(&transform), xOffset(0), yOffset(0) {
        assert(this->transform != nullptr && "TransformComponent cannot be null!");
        collider.x = static_cast<int>(this->transform->position.x) + xOffset * this->transform->scale;
        collider.y = static_cast<int>(this->transform->position.y) + yOffset * this->transform->scale;
        collider.w = this->transform->width * this->transform->scale;
        collider.h = this->transform->height * this->transform->scale;
    }

    explicit ColliderComponent(TransformComponent &transform, int w, int h, int xOffset, int yOffset)
        : transform(&transform), xOffset(xOffset), yOffset(yOffset) {
        assert(this->transform != nullptr && "TransformComponent cannot be null!");
        collider.x = static_cast<int>(this->transform->position.x) + xOffset * this->transform->scale;
        collider.y = static_cast<int>(this->transform->position.y) + yOffset * this->transform->scale;
        collider.w = w * this->transform->scale;
        collider.h = h * this->transform->scale;
    }

    void update() override {
        collider.x = static_cast<int>(this->transform->position.x) + xOffset * this->transform->scale;
        collider.y = static_cast<int>(this->transform->position.y) + yOffset * this->transform->scale;
    }

    void render() {
        // For debuging
        SDL_RenderDrawRect(Game::renderer, &collider);
        SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    }

private:
    TransformComponent *transform;
    int xOffset, yOffset;
};
