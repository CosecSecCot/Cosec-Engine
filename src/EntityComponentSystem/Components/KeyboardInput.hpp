#pragma once

#include "Game.hpp"
#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "Utils/Vector2D.hpp"

class KeyboardInput : public Component {
public:
    KeyboardInput() = delete;
    explicit KeyboardInput(TransformComponent &transform) : transform(&transform) {}

    void update() override {
        transform->velocity.x = 0;
        transform->velocity.y = 0;

        if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) {
            transform->velocity.y = -1;
        }
        if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) {
            transform->velocity.x = -1;
        }
        if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]) {
            transform->velocity.y = 1;
        }
        if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
            transform->velocity.x = 1;
        }
    }

private:
    TransformComponent *transform;
    const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
};
