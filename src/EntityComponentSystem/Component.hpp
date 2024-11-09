#ifndef Component_hpp
#define Component_hpp
#pragma once

#include <bitset>
#include <cstddef>
#include <type_traits>

constexpr const std::size_t maxComponents = 32;

using ComponentID = std::size_t;
using ComponentMask = std::bitset<maxComponents>;

class Component {
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void update() = 0;
};

inline ComponentID getUniqueComponentID() {
    // lastID is only once and
    // not initialized in the later calls.
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

    // typeID gets initialized once only
    // when a type calls this function for the first time
    // on subsequent calls, the initalization line is skipped
    // because it uses the already initialized value (because of static).
    static ComponentID typeID = getUniqueComponentID();
    return typeID;
}

#endif /* Component.hpp */
