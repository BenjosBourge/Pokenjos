/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include "entity.hpp"

class System {
public:
    Signature _signature;
    std::vector<Entity> _entities;
    std::vector<Entity> _entitiesThisFrame;

    virtual void update(float deltaTime) = 0;
    virtual void addedEntity(Entity entity) = 0;
    virtual void removedEntity(Entity entity) = 0;
};
