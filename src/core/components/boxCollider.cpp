/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/boxCollider.hpp"

BoxCollider::BoxCollider()
{
    _width = 0;
    _height = 0;
    _offsetX = 0;
    _offsetY = 0;
    _mask = 0;
    _chunck = -1;
}

BoxCollider::BoxCollider(float width, float height) : BoxCollider()
{
    _width = width;
    _height = height;
}

BoxCollider::BoxCollider(float width, float height, float offsetX, float offsetY) : BoxCollider()
{
    _width = width;
    _height = height;
    _offsetX = offsetX;
    _offsetY = offsetY;
}

BoxCollider::BoxCollider(float width, float height, float offsetX, float offsetY, int mask) : BoxCollider()
{
    _width = width;
    _height = height;
    _offsetX = offsetX;
    _offsetY = offsetY;
    _mask = mask;
}

BoxCollider::~BoxCollider()
{

}
