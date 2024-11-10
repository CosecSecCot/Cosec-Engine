#include "Entity.hpp"
#include "EntityComponentSystem/Components/ColliderComponent.hpp"
#include "EntityComponentSystem/Components/TextureComponent.hpp"

Entity::Entity() = default;

Entity::~Entity() = default;

void Entity::update() {
    for (auto &&[id, component] : components) {
        component->update();
    }
}

void Entity::render() const {
    // Draw only those components which have SpriteComponent attached
    // else draw a margenta color
    if (hasComponent<TextureComponent>()) {
        getComponent<TextureComponent>()->render();
    }

    // if (hasComponent<ColliderComponent>()) {
    //     getComponent<ColliderComponent>()->render();
    // }
}
