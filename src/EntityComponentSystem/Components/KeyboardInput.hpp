#pragma once

#include "EntityComponentSystem/Components/AnimationComponent.hpp"
#include "Game.hpp"

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "Utils/Vector2D.hpp"

class KeyboardInput : public Component {
public:
    KeyboardInput() = delete;
    explicit KeyboardInput(TransformComponent &transform, AnimationComponent &animation)
        : transform(&transform), animation(&animation) {}

    void update() override {
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
        if ((Game::keyboardState[SDLK_UP] || Game::keyboardState[SDLK_w]) &&
            (Game::keyboardState[SDLK_DOWN] || Game::keyboardState[SDLK_s])) {
            transform->velocity.y = 0;
        } else if (Game::keyboardState[SDLK_UP] || Game::keyboardState[SDLK_w]) {
            transform->velocity.y = -1;
            animation->play("walkUp");
            animation->flipReset();
        } else if (Game::keyboardState[SDLK_DOWN] || Game::keyboardState[SDLK_s]) {
            transform->velocity.y = 1;
            animation->play("walkDown");
            animation->flipReset();
        }

        if ((Game::keyboardState[SDLK_LEFT] || Game::keyboardState[SDLK_a]) &&
            (Game::keyboardState[SDLK_RIGHT] || Game::keyboardState[SDLK_d])) {
            transform->velocity.x = 0;
        } else if (Game::keyboardState[SDLK_LEFT] || Game::keyboardState[SDLK_a]) {
            transform->velocity.x = -1;
            animation->play("walkSide");
            animation->flipHorizontal();
        } else if (Game::keyboardState[SDLK_RIGHT] || Game::keyboardState[SDLK_d]) {
            transform->velocity.x = 1;
            animation->play("walkSide");
            animation->flipReset();
        }
    }

private:
    TransformComponent *transform;
    AnimationComponent *animation;
};
