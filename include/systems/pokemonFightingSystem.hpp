/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../core/system.hpp"
#include "../components/match.hpp"

class PokemonFightingSystem : public System {
public:
    PokemonFightingSystem();
    ~PokemonFightingSystem();

    void update(float deltaTime) override;
    void addedEntity(Entity entity) override;
    void removedEntity(Entity entity) override;

    void PokemonIdleAnimation(float deltaTime, Match &match);
};
