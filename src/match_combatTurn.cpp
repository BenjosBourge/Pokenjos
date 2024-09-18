/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include <vector>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "../include/core/coordinator.hpp"
#include "../include/core/ecs.hpp"
#include "../include/core/components/transform.hpp"
#include "../include/prefabPokemon.hpp"
#include "../include/components/match.hpp"
#include "../include/components/trainer.hpp"
#include "../include/core/components/ui.hpp"
#include "../include/core/components/text.hpp"
#include "../include/matchMethods.hpp"

void match_attackAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "Attack sequence";
}

void match_showAttacks(Entity match);

void match_attackAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "";

    match_showPokemonInfos();
    match_showAttacks(match);
}

void match_launchAttack(Entity self)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");

    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &trainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);

    matchComponent._timeAnimation = 3.f;
    matchComponent.setAnimation(match_attackAnimation, match_attackAnimationFinished);

    std::vector<Entity> entities = coordinator->getEntitiesFromTag("attack");
    for (auto &entity : entities)
        coordinator->killEntity(entity);

    match_removePokemonInfos();
}

