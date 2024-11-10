#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "Utils/Vector2D.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    float speed = 3;

    TransformComponent() : position(Vector2D(0, 0)) {}
    TransformComponent(float x, float y) : position(Vector2D(x, y)) {}

    void update() override {
        position += (speed * velocity);
    }
};
