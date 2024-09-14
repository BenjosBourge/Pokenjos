/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../texture.hpp"
#include "../entity.hpp"

class InteractionBoxCollider {
public:
    InteractionBoxCollider();
    InteractionBoxCollider(float width, float height);
    InteractionBoxCollider(float width, float height, float offsetX, float offsetY);
    InteractionBoxCollider(float width, float height, float offsetX, float offsetY, bool isTrigger);
    ~InteractionBoxCollider();

    float _width;
    float _height;
    float _offsetX;
    float _offsetY;
    std::vector<Entity> _entitiesCollided;
    bool _isTrigger;
};