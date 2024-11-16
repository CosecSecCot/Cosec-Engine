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

        this->width = this->transform->width;
        this->height = this->transform->height;
    }

    explicit ColliderComponent(TransformComponent &transform, int w, int h, int xOffset, int yOffset)
        : transform(&transform), width(w), height(h), xOffset(xOffset), yOffset(yOffset) {
        assert(this->transform != nullptr && "TransformComponent cannot be null!");
        collider.x = static_cast<int>(this->transform->position.x) + xOffset * this->transform->scale;
        collider.y = static_cast<int>(this->transform->position.y) + yOffset * this->transform->scale;
        collider.w = w * this->transform->scale;
        collider.h = h * this->transform->scale;
    }

    void update() override {
        // Lets say we adjusted the scale during a frame
        // then collider's size should also change
        collider.w = this->width * this->transform->scale;
        collider.h = this->height * this->transform->scale;

        collider.x = static_cast<int>(this->transform->position.x) + xOffset * this->transform->scale;
        collider.y = static_cast<int>(this->transform->position.y) + yOffset * this->transform->scale;
    }

    void debug() {
        assert(Game::renderer != nullptr && "Renderer cannot be null.");
        if (!Game::renderDebug)
            return;

        SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(Game::renderer, &collider);
    }

    static bool Collision(const SDL_Rect &rect1, const SDL_Rect &rect2, SDL_Rect &intersection) {
        return SDL_IntersectRect(&rect1, &rect2, &intersection);
    }

private:
    TransformComponent *transform;
    int xOffset, yOffset;
    int width, height;
};
