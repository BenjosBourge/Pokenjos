/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/trailSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/components/trail.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/components/lifeTimer.hpp"

TrailSystem::TrailSystem()
{
    _signature = getCoordinator()->getComponentSignature<Trail>();
    _signature |= getCoordinator()->getComponentSignature<SpriteRenderer>();
    _signature |= getCoordinator()->getComponentSignature<Transform>();
}

TrailSystem::~TrailSystem()
{

}

void TrailSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const& entity : _entitiesThisFrame) {
        auto &trail = coordinator->getComponent<Trail>(entity);
        auto &spriteRenderer = coordinator->getComponent<SpriteRenderer>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

        if (trail._isActive) {
            trail._currentTimerSpawn -= deltaTime;
            if (trail._currentTimerSpawn <= 0) {
                trail._currentTimerSpawn = trail._timerSpawn;
                Entity e = coordinator->createEntity();
                coordinator->addComponent<Transform>(e, transform);
                SpriteRenderer nsp = spriteRenderer;
                coordinator->addComponent<SpriteRenderer>(e, spriteRenderer);
                coordinator->addComponent<LifeTimer>(e, LifeTimer(0.3f, true));
            }
        }
    }
}

void TrailSystem::addedEntity(Entity entity)
{

}

void TrailSystem::removedEntity(Entity entity)
{

}