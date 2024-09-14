/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../system.hpp"

class DrawSystem : public System {
public:
    DrawSystem();
    ~DrawSystem();

    void update(float deltaTime) override;
    void addedEntity(Entity entity) override;
    void removedEntity(Entity entity) override;

    void layerChanged(Entity entity);
    void yChanged(Entity entity);
};
