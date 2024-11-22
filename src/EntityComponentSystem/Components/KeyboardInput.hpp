#pragma once

#include "EntityComponentSystem/Components/AnimationComponent.hpp"
#include "Game.hpp"
#include <unordered_map>

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "Utils/Vector2D.hpp"

class KeyboardInput : public Component {
public:
    KeyboardInput() = delete;
    explicit KeyboardInput(TransformComponent &transform, AnimationComponent &animation)
        : transform(&transform), animation(&animation) {}

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

        // Assuming: For this frame player is not moving
        if (transform->velocity.x < 0) {
            animation->play("idleSide");
            animation->flipHorizontal();
        } else if (transform->velocity.x > 0) {
            animation->play("idleSide");
            animation->flipReset();
        } else if (transform->velocity.y < 0) {
            animation->play("idleUp");
            animation->flipReset();
        } else if (transform->velocity.y > 0) {
            animation->play("idleDown");
            animation->flipReset();
        }
        transform->velocity = {0, 0};

        // For each frame, we are seeing in which direction
        // player is trying to move
        if ((keyboardState[SDLK_UP] || keyboardState[SDLK_w]) && (keyboardState[SDLK_DOWN] || keyboardState[SDLK_s])) {
            transform->velocity.y = 0;
        } else if (keyboardState[SDLK_UP] || keyboardState[SDLK_w]) {
            transform->velocity.y = -1;
            animation->play("walkUp");
            animation->flipReset();
        } else if (keyboardState[SDLK_DOWN] || keyboardState[SDLK_s]) {
            transform->velocity.y = 1;
            animation->play("walkDown");
            animation->flipReset();
        }

        if ((keyboardState[SDLK_LEFT] || keyboardState[SDLK_a]) &&
            (keyboardState[SDLK_RIGHT] || keyboardState[SDLK_d])) {
            transform->velocity.x = 0;
        } else if (keyboardState[SDLK_LEFT] || keyboardState[SDLK_a]) {
            transform->velocity.x = -1;
            animation->play("walkSide");
            animation->flipHorizontal();
        } else if (keyboardState[SDLK_RIGHT] || keyboardState[SDLK_d]) {
            transform->velocity.x = 1;
            animation->play("walkSide");
            animation->flipReset();
        }
    }

private:
    TransformComponent *transform;
    AnimationComponent *animation;
    std::unordered_map<SDL_Keycode, bool> keyboardState;
};
