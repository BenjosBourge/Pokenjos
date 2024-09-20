/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include <vector>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "../include/core/myMath.hpp"
#include "../include/core/coordinator.hpp"
#include "../include/core/ecs.hpp"
#include "../include/core/components/transform.hpp"
#include "../include/prefabPokemon.hpp"
#include "../include/components/match.hpp"
#include "../include/components/trainer.hpp"
#include "../include/core/components/ui.hpp"
#include "../include/core/components/text.hpp"
#include "../include/matchMethods.hpp"

void match_showAttacks(Entity match);

void match_lifebarAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //make the tuple
    Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "lifeBar animation!";
}

void match_lifebarAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    match_showAttacks(match);
}

void match_flickeringAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //make the tuple
    Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "Flickering animation!";
}

void match_flickeringAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    matchComponent._timeAnimation = 2.f;

    match_showPokemonInfos();
    matchComponent.setAnimation(match_lifebarAnimation, match_lifebarAnimationFinished);
}


void match_attackAnimation(Entity match, float deltaTime)
{
    std::cout << "MAMMA MIA" << std::endl;
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //make the tuple
    std::cout << matchComponent._attacksOrder.size() << std::endl;
    Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);

    std::cout << "YAHOO" << std::endl;

    auto &trainerAttackingComponent = coordinator->getComponent<Trainer>(trainerAttacking);
    auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = trainerAttackingComponent._name + " attacks " + trainerDefendingComponent._name + "!";
}

void match_attackAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    /*Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);

    auto &trainerAttackingComponent = coordinator->getComponent<Trainer>(trainerAttacking);

    Entity spriteAttacking = NULL_ENTITY;
    Entity spriteDefending = NULL_ENTITY;

    if (trainerAttackingComponent._id == 0) {
        spriteAttacking = matchComponent._spritePlayer;
        spriteDefending = matchComponent._spriteOpponent;
    } else {
        spriteAttacking = matchComponent._spriteOpponent;
        spriteDefending = matchComponent._spritePlayer;
    }

    auto &transformSpriteAttacking = coordinator->getComponent<Transform>(spriteAttacking);*/

    matchComponent._timeAnimation = 3.f;
    matchComponent.setAnimation(match_flickeringAnimation, match_flickeringAnimationFinished);
}


void match_startAttackAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "Attack sequence Loading...";
}

void match_startAttackAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "";

    matchComponent._timeAnimation = 3.f;
    matchComponent.setAnimation(match_attackAnimation, match_attackAnimationFinished);
}


void match_setupCombatSequence()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");

    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &trainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);

    std::vector<Entity> entities = coordinator->getEntitiesFromTag("attack");
    for (auto &entity : entities)
        coordinator->killEntity(entity);

    matchComponent._attacksOrder.clear();
    matchComponent._attacksOrder.push_back(std::make_tuple(matchComponent._trainersPlayer[0], matchComponent._trainersOpponent[0], 0));
    matchComponent._attacksOrder.push_back(std::make_tuple(matchComponent._trainersOpponent[0], matchComponent._trainersPlayer[0], 0));

    matchComponent._timeAnimation = 1.f;
    matchComponent.setAnimation(match_startAttackAnimation, match_startAttackAnimationFinished);
}


void match_launchAttack(Entity self)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");

    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &trainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);

    std::vector<Entity> entities = coordinator->getEntitiesFromTag("attack");
    for (auto &entity : entities)
        coordinator->killEntity(entity);
    match_removePokemonInfos();

    match_setupCombatSequence();
}

