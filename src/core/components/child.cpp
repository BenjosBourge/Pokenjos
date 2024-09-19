/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/child.hpp"
#include "../../../include/core/coordinator.hpp"
#include "../../../include/core/components/transform.hpp"

Child::Child()
{
    _parent = NULL_ENTITY;
    _xOffset = 0;
    _yOffset = 0;
    _ratioScale = {1, 1};
    _syncOpacity = false;
}

Child::Child(Entity parent) : Child()
{
    _parent = parent;
}

/*To automatically set the offset and scale of the child to the parent's*/
Child::Child(Entity parent, Entity child) : Child()
{
    _parent = parent;
    if (getCoordinator()->hasComponent<Transform>(child) && getCoordinator()->hasComponent<Transform>(parent)) {
        auto &transform = getCoordinator()->getComponent<Transform>(child);
        auto &parentTransform = getCoordinator()->getComponent<Transform>(parent);

        _xOffset = transform._x;
        _yOffset = transform._y;
        _ratioScale = {transform._width / parentTransform._width, transform._height / parentTransform._height};
    }
}

Child::Child(Entity parent, int xOffset, int yOffset) : Child()
{
    _parent = parent;
    _xOffset = xOffset;
    _yOffset = yOffset;
}

Child::Child(Entity parent, int xOffset, int yOffset, float ratioScale) : Child()
{
    _parent = parent;
    _xOffset = xOffset;
    _yOffset = yOffset;
    _ratioScale = {ratioScale, ratioScale};
}

Child::~Child()
{

}
