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

#define LAYER_COLLISION_PLAYER 0b1
#define LAYER_COLLISION_ENEMY 0b10

class BoxCollider {
public:
    BoxCollider();
    BoxCollider(float width, float height);
    BoxCollider(float width, float height, float offsetX, float offsetY);
    BoxCollider(float width, float height, float offsetX, float offsetY, int mask);
    ~BoxCollider();

    float _width;
    float _height;
    float _offsetX;
    float _offsetY;
    std::vector<Entity> _entitiesCollided;
    int _mask;
    int _chunck;
};