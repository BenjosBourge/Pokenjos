/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/childSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/components/child.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"

ChildSystem::ChildSystem()
{
    _signature = getCoordinator()->getComponentSignature<Child>();
}

ChildSystem::~ChildSystem()
{

}

void ChildSystem::update(float deltaTime)
{
    for (auto const& entity : _entitiesThisFrame) {
        auto &child = getCoordinator()->getComponent<Child>(entity);

        if (child._parent == NULL_ENTITY)
            continue;
        if (getCoordinator()->hasComponent<Transform>(entity) && getCoordinator()->hasComponent<Transform>(child._parent)) {
            auto &transform = getCoordinator()->getComponent<Transform>(entity);
            auto &parentTransform = getCoordinator()->getComponent<Transform>(child._parent);

            transform._x = parentTransform._x + child._xOffset * (parentTransform._width * child._ratioScale.x) / transform._width;
            transform._y = parentTransform._y + child._yOffset * (parentTransform._height * child._ratioScale.y) / transform._height;
            transform._width = parentTransform._width * child._ratioScale.x;
            transform._height = parentTransform._height * child._ratioScale.y;
        }

        if (child._syncOpacity)
            if (getCoordinator()->hasComponent<SpriteRenderer>(entity) && getCoordinator()->hasComponent<SpriteRenderer>(child._parent)) {
                auto &spriteRenderer = getCoordinator()->getComponent<SpriteRenderer>(entity);
                auto &parentSpriteRenderer = getCoordinator()->getComponent<SpriteRenderer>(child._parent);

                spriteRenderer._opacity = parentSpriteRenderer._opacity;
            }
    }
}

void ChildSystem::addedEntity(Entity entity)
{

}

void ChildSystem::removedEntity(Entity entity)
{

}