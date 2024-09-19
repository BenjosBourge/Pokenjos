/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/pokemonFightingSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/match.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/components/tag.hpp"
#include "../../../../include/core/components/child.hpp"

PokemonFightingSystem::PokemonFightingSystem()
{
    _signature = getCoordinator()->getComponentSignature<Match>();
}

PokemonFightingSystem::~PokemonFightingSystem()
{

}

void PokemonFightingSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const& entity : _entitiesThisFrame) {
        auto &match = coordinator->getComponent<Match>(entity);

        if (match._timeAnimation > 0.0f) {
            //make an animation
            match._loopingTimer = 0.0f;
            match._timeAnimation -= deltaTime;
            if (match._timeAnimation <= 0.0f) {
                match._timeAnimation = 0.0f;
                if (match._animation != nullptr)
                    match._animation(entity, deltaTime);
                if (match._animationEnded != nullptr)
                    match._animationEnded(entity);
            } else {
                if (match._animation != nullptr)
                    match._animation(entity, deltaTime);
            }
            continue;
        }

        match._loopingTimer += deltaTime;
        if (match._loopingTimer >= 1.0f)
            match._loopingTimer -= 1.0f;

        auto &transformSpritePlayer = coordinator->getComponent<Transform>(match._spritePlayer);
        Entity playerInfo = NULL_ENTITY;

        std::vector<Entity> entities = coordinator->getEntitiesFromTag("InfoPlayer");
        for (auto &e : entities) {
            if (!coordinator->hasComponent<Child>(e)) {
                playerInfo = e;
                break;
            }
        }

        transformSpritePlayer._y = -95;
        if (match._loopingTimer < 0.25f) {
            transformSpritePlayer._y = -90;
        } else if (match._loopingTimer < 0.75f && match._loopingTimer >= 0.5f) {
            transformSpritePlayer._y = -100;
        }

        if (playerInfo != NULL_ENTITY) {
            auto &transformPlayerInfo = coordinator->getComponent<Transform>(playerInfo);
            transformPlayerInfo._y = 10;
            if (match._loopingTimer < 0.25f) {
                transformPlayerInfo._y = 5;
            } else if (match._loopingTimer < 0.75f && match._loopingTimer >= 0.5f) {
                transformPlayerInfo._y = 15;
            }
        } else
            std::cout << "Error: No playerInfo entity" << std::endl;
    }
}

void PokemonFightingSystem::addedEntity(Entity entity)
{

}

void PokemonFightingSystem::removedEntity(Entity entity)
{

}
