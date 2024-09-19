/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include <SFML/Graphics.hpp>
#include "../texture.hpp"
#include "../entity.hpp"

class Child {
public:
    Child();
    Child(Entity parent);
    Child(Entity parent, Entity child);
    Child(Entity parent, int xOffset, int yOffset);
    Child(Entity parent, int xOffset, int yOffset, float ratioScale);
    ~Child();

    Entity _parent;
    int _xOffset;
    int _yOffset;
    sf::Vector2f _ratioScale;
    bool _syncOpacity;
};