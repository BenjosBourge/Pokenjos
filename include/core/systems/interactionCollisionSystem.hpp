/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../system.hpp"

class InteractionCollisionSystem : public System {
public:
    InteractionCollisionSystem();
    ~InteractionCollisionSystem();

    void update(float deltaTime) override;
    void addedEntity(Entity entity) override;
    void removedEntity(Entity entity) override;

private:
    std::vector<Entity> _entitiesTrigger;
};
