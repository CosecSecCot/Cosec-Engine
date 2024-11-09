#pragma once

#include "EntityComponentSystem/Component.hpp"

class PositionComponent : public Component {
public:
    PositionComponent() : xPosition(0), yPosition(0) {}
    PositionComponent(int x, int y) : xPosition(x), yPosition(y) {}

    void update() override {
        xPosition++;
        yPosition++;
    }

    [[nodiscard]] int x() const {
        return xPosition;
    };
    [[nodiscard]] int y() const {
        return xPosition;
    };
    void setX(int x) {
        this->xPosition = x;
    }
    void setY(int y) {
        this->yPosition = y;
    }
    void setPosition(int x, int y) {
        this->xPosition = x;
        this->yPosition = y;
    }

private:
    int xPosition, yPosition;
};
