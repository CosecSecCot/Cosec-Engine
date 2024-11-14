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

    SDL_Rect intersection;
    if (ColliderComponent::Collision(collider->collider, otherCollider->collider, intersection)) {
        auto transform = this->getComponent<TransformComponent>();
        auto otherTransform = other.getComponent<TransformComponent>();

        if (intersection.w < intersection.h) {
            if (collider->collider.x < otherCollider->collider.x) {
                transform->position.x -= static_cast<float>(intersection.w);
            } else {
                transform->position.x += static_cast<float>(intersection.w);
            }
        } else {
            if (collider->collider.y < otherCollider->collider.y) {
                transform->position.y -= static_cast<float>(intersection.h);
            } else {
                transform->position.y += static_cast<float>(intersection.h);
            }
        }
    }
}
