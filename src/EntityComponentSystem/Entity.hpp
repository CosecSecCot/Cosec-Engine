#ifndef Entity_hpp
#define Entity_hpp
#pragma once

#include "EntityComponentSystem/Component.hpp"

#include <cassert>
#include <map>
#include <memory>

class Entity {
public:
    Entity();
    ~Entity();

    [[nodiscard]] bool isActive() const {
        return active;
    }

    void update();
    void render() const;
    void destroy() {
        this->active = false;
    }

    template <class T> [[nodiscard]] bool hasComponent() const {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

        return componentMask[getComponentTypeID<T>()];
    }

    template <class... TArgs> [[nodiscard]] bool hasComponents() const {
        // Fold operator, reads as
        // (hasComponent<Transform>() && hasComponent<Physics>() && hasComponent<Sprite>() && ...)
        return (hasComponent<TArgs>() && ...);
    }

    template <class T, class... TArgs> T &addComponent(TArgs &&...componentArgs) {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

        auto componentID = getComponentTypeID<T>();

        // making a unique_ptr to the Component
        // by passing the args into its constructor
        //
        // Fix: Explicitly pass args to std::forward<T>(args)
        // see
        // https://stackoverflow.com/questions/48501797/no-matching-function-for-call-stdforwardconst-stdstring-with-variadic-ar
        std::unique_ptr<T> component = std::make_unique<T>(std::forward<TArgs>(componentArgs)...);

        // passing the ownership of the pointer
        // to the map of all components
        if (components.find(componentID) == components.end()) {
            components.emplace(componentID, std::move(component));
        }

        // Explicitly setting to nullptr after moving
        component = nullptr;

        // Since the component has been added
        // setting the bit in the mask
        componentMask[componentID] = true;

        // Return the stored component
        // (is still owned by components map)
        return *static_cast<T *>(components[componentID].get());
    }

    template <class T> T &getComponent() const {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

        auto it = components.find(getComponentTypeID<T>());
        if (it != components.end()) {
            return *static_cast<T *>(it->second.get());
        }

        throw *static_cast<T *>(nullptr);
    }

    template <class T> void removeComponent() {
        assert(false && "removeComponent<T>() has not been implemented yet.");
    }

    template <class... T> void removeComponents() {
        assert(false && "removeComponent<T>() has not been implemented yet.");
    }

private:
    bool active = true;
    std::map<ComponentID, std::unique_ptr<Component>> components;
    ComponentMask componentMask;
};

#endif /* Entity.hpp */
