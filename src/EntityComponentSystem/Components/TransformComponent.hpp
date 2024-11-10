#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "Utils/Vector2D.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    float speed = 3;

    int width, height;
    uint16_t scale = 1;

    TransformComponent(int w, int h) : position(Vector2D(0, 0)), width(w), height(h) {}
    TransformComponent(float x, float y, int w, int h) : position(Vector2D(x, y)), width(w), height(h) {}

    void update() override {
        position += (speed * velocity);
    }
};
