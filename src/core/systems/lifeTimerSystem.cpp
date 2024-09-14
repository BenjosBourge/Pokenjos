/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/lifeTimerSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/components/lifeTimer.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"

LifeTimerSystem::LifeTimerSystem()
{
    _signature = getCoordinator()->getComponentSignature<LifeTimer>();
}

LifeTimerSystem::~LifeTimerSystem()
{

}

void LifeTimerSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const& entity : _entitiesThisFrame) {
        auto &lifeTimer = coordinator->getComponent<LifeTimer>(entity);

        lifeTimer._lifeTime -= deltaTime;
        if (lifeTimer._lifeTime <= 0)
            coordinator->killEntity(entity);
        if (lifeTimer._decreasingOpacity) {
            if (!coordinator->hasComponent<SpriteRenderer>(entity))
                continue;
            auto &spriteRenderer = coordinator->getComponent<SpriteRenderer>(entity);
            spriteRenderer._opacity = lifeTimer._lifeTime / lifeTimer._maxLifeTime;
        }
    }
}

void LifeTimerSystem::addedEntity(Entity entity)
{

}

void LifeTimerSystem::removedEntity(Entity entity)
{

}