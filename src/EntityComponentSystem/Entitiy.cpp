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

void Entity::resolveStaticCollision(const Entity &other) const {
    if (!this->hasComponents<TransformComponent, ColliderComponent>() ||
        !other.hasComponents<TransformComponent, ColliderComponent>()) {
        return;
    }

    auto collider = this->getComponent<ColliderComponent>();
    auto otherCollider = other.getComponent<ColliderComponent>();

    if (ColliderComponent::Collision(collider->collider, otherCollider->collider)) {
        auto transform = this->getComponent<TransformComponent>();
        auto otherTransform = other.getComponent<TransformComponent>();

        // TODO: do something about collision
    }
}
