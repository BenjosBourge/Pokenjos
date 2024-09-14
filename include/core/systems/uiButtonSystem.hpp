/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../system.hpp"

class UiButtonSystem : public System {
public:
    UiButtonSystem();
    ~UiButtonSystem();

    void update(float deltaTime) override;
    void addedEntity(Entity entity) override;
    void removedEntity(Entity entity) override;
};
