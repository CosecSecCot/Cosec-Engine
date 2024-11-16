#include "ECS.hpp"
#include "EntityComponentSystem/Components/TextureComponent.hpp"
#include <algorithm>

void ECS::update() {
    for (auto &entity : this->entities) {
        entity->update();
    }
}

void ECS::render() {
    std::sort(entities.begin(), entities.end(), [](std::unique_ptr<Entity> &a, std::unique_ptr<Entity> &b) {
        if (!(a->hasComponent<TextureComponent>() && b->hasComponent<TextureComponent>()))
            return false;
        return a->getComponent<TextureComponent>()->pivot.y < b->getComponent<TextureComponent>()->pivot.y;
    });

    for (auto &entity : this->entities) {
        entity->render();
    }
}

void ECS::refresh() {
    assert(false && "ECS::refresh() has not been implemented yet");
}

Entity &ECS::addEntity() {
    // Creating a new entity dynamically
    auto *entity = new Entity();

    // transfering entity's ownership to a unique_ptr
    // thus it is not required to free it right now
    std::unique_ptr<Entity> entity_ptr(entity);

    // ownership transfered to entities vector
    this->entities.emplace_back(std::move(entity_ptr));

    return *entity;
}
