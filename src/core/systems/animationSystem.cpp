/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/animationSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"
#include "../../../../include/core/components/animator.hpp"

AnimationSystem::AnimationSystem()
{
    _signature = getCoordinator()->getComponentSignature<Animator>();
    _signature |= getCoordinator()->getComponentSignature<SpriteRenderer>();
}

AnimationSystem::~AnimationSystem()
{

}

void AnimationSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const& entity : _entitiesThisFrame) {
        auto &animator = coordinator->getComponent<Animator>(entity);
        auto &spriteRenderer = coordinator->getComponent<SpriteRenderer>(entity);

        if (animator._currentAnimation._numberOfFrames == 0)
            continue;
        animator._currentFrame %= animator._currentAnimation._numberOfFrames;
        animator._time += deltaTime;
        if (animator._time >= animator._currentAnimation._frameTime) {
            animator._time = 0;
            animator._currentFrame++;
            if (animator._currentAnimation._isLooping)
                animator._currentFrame %= animator._currentAnimation._numberOfFrames;
            else
                animator._currentFrame = std::min(animator._currentFrame, animator._currentAnimation._numberOfFrames - 1);
        }
        spriteRenderer._offsetX = animator._currentFrame * spriteRenderer._rectWidth;
        spriteRenderer._offsetY = animator._verticalOffset * spriteRenderer._rectHeight;
    }
}

void AnimationSystem::addedEntity(Entity entity)
{

}

void AnimationSystem::removedEntity(Entity entity)
{

}