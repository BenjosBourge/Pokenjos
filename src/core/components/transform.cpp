/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/components/transform.hpp"

Transform::Transform()
{
    _x = 0;
    _y = 0;
    _width = 1;
    _height = 1;
}

Transform::Transform(float x, float y)
{
    _x = x;
    _y = y;
    _width = 0;
    _height = 0;
}

Transform::Transform(float x, float y, float width, float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}

Transform::~Transform()
{

}