#ifndef ECS_hpp
#define ECS_hpp
#pragma once

#include "EntityComponentSystem/Entity.hpp"

#include <vector>

class ECS {
public:
    void update();
    void render();
    void refresh();

    Entity &addEntity();

private:
    std::vector<std::unique_ptr<Entity>> entities;
};

#endif /* ECS.hpp */
