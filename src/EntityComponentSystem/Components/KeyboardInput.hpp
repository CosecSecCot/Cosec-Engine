#pragma once

#include "Game.hpp"
#include <unordered_map>

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "Utils/Vector2D.hpp"

class KeyboardInput : public Component {
public:
    KeyboardInput() = delete;
    explicit KeyboardInput(TransformComponent &transform) : transform(&transform) {}

    void update() override {
        switch (Game::event.type) {
        case SDL_KEYDOWN:
            keyboardState[Game::event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keyboardState[Game::event.key.keysym.sym] = false;
            break;
        default:
            break;
        }

        // For each frame calculate velocity
        // inidividually
        transform->velocity = {0, 0};

        if (keyboardState[SDLK_UP] || keyboardState[SDLK_w]) {
            if (transform->velocity.y == 1)
                transform->velocity.y = 0;
            else
                transform->velocity.y = -1;
        }

        if (keyboardState[SDLK_LEFT] || keyboardState[SDLK_a]) {
            if (transform->velocity.x == 1)
                transform->velocity.x = 0;
            else
                transform->velocity.x = -1;
        }

        if (keyboardState[SDLK_DOWN] || keyboardState[SDLK_s]) {
            if (transform->velocity.y == -1)
                transform->velocity.y = 0;
            else
                transform->velocity.y = 1;
        }

        if (keyboardState[SDLK_RIGHT] || keyboardState[SDLK_d]) {
            if (transform->velocity.x == -1)
                transform->velocity.x = 0;
            else
                transform->velocity.x = 1;
        }
    }

private:
    TransformComponent *transform;
    std::unordered_map<SDL_Keycode, bool> keyboardState;
};
