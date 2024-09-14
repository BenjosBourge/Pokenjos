/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../system.hpp"

class CollisionSystem : public System {
public:
    CollisionSystem();
    ~CollisionSystem();

    void update(float deltaTime) override;
    void addedEntity(Entity entity) override;
    void removedEntity(Entity entity) override;

    std::vector<std::vector<Entity>> _chuncks;

    void entityMoved(Entity entity);
    void removeEntityChunck(Entity entity);
    void setEntityChunck(Entity entity);
    std::vector<Entity> getAllEntitiesNear(int thisChunck);
};
