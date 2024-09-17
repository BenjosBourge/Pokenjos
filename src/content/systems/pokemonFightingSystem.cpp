/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/pokemonFightingSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/match.hpp"

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
    }
}

void PokemonFightingSystem::addedEntity(Entity entity)
{

}

void PokemonFightingSystem::removedEntity(Entity entity)
{

}
