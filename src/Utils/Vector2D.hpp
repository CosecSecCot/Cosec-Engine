#ifndef Vector2D_hpp
#define Vector2D_hpp
#pragma once

#include <cmath>
#include <iostream>

class Vector2D {
public:
    float x, y;

    Vector2D() : x(0), y(0) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D &other) const {
        return {x + other.x, y + other.y};
    }

    Vector2D operator-(const Vector2D &other) const {
        return {x - other.x, y - other.y};
    }

    Vector2D &operator+=(const Vector2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D &operator-=(const Vector2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    friend Vector2D operator*(float scalar, const Vector2D &other) {
        return {other.x * scalar, other.y * scalar};
    }

    friend Vector2D operator/(float scalar, const Vector2D &other) {
        return {other.x / scalar, other.y / scalar};
    }

    Vector2D &operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D &operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vector2D &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2D &other) const {
        return !(*this == other);
    }

    // Assignment operator
    Vector2D &operator=(const Vector2D &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // Debuging
    friend std::ostream &operator<<(std::ostream &stream, const Vector2D &other) {
        stream << "(" << other.x << ", " << other.y << ")";
        return stream;
    }

    // Utility methods
    [[nodiscard]] float magnitude() const {
        return std::sqrt((x * x) + (y * y));
    }

    [[nodiscard]] Vector2D normalized() const {
        float mag = magnitude();
        return (mag == 0) ? Vector2D(0, 0) : Vector2D(x / mag, y / mag);
    }
};

#endif /* Vector2D.hpp */
