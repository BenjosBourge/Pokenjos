/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../system.hpp"

class TextRenderingSystem : public System {
public:
    TextRenderingSystem();
    ~TextRenderingSystem();

    void update(float deltaTime) override;
    void addedEntity(Entity entity) override;
    void removedEntity(Entity entity) override;
};
