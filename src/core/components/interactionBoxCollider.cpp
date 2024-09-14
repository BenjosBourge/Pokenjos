/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/interactionBoxCollider.hpp"

InteractionBoxCollider::InteractionBoxCollider()
{
    _width = 0;
    _height = 0;
    _offsetX = 0;
    _offsetY = 0;
    _isTrigger = false;
}

InteractionBoxCollider::InteractionBoxCollider(float width, float height)
{
    _width = width;
    _height = height;
    _offsetX = 0;
    _offsetY = 0;
    _isTrigger = false;
}

InteractionBoxCollider::InteractionBoxCollider(float width, float height, float offsetX, float offsetY)
{
    _width = width;
    _height = height;
    _offsetX = offsetX;
    _offsetY = offsetY;
    _isTrigger = false;
}

InteractionBoxCollider::InteractionBoxCollider(float width, float height, float offsetX, float offsetY, bool isTrigger)
{
    _width = width;
    _height = height;
    _offsetX = offsetX;
    _offsetY = offsetY;
    _isTrigger = isTrigger;
}

InteractionBoxCollider::~InteractionBoxCollider()
{

}
