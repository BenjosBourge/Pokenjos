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
#include "../include/core/components/spriteRenderer.hpp"
#include "../include/core/components/child.hpp"

void new_attackSequence(Entity match);

void match_faintingAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //make the tuple
    Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "Fainting animation!";
}

void match_faintingAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //pop front
    std::vector<std::tuple<Entity, Entity, int>> newAttacksOrder;
    for (int i = 1; i < matchComponent._attacksOrder.size(); i++)
        newAttacksOrder.push_back(matchComponent._attacksOrder[i]);
    matchComponent._attacksOrder = newAttacksOrder;

    new_attackSequence(match);
}

void match_lifebarAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //make the tuple
    Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);
    auto &pokemon = coordinator->getComponent<Trainer>(trainerDefending)._pokemons[0];

    int idDefending = coordinator->getComponent<Trainer>(trainerDefending)._id;
    Entity lifeBar = coordinator->getEntityFromTag("lifebar_" + std::to_string(idDefending));

    float ratio = matchComponent._timeAnimation / 1.f;
    pokemon._currentHP = pokemon._pvFrom + (pokemon._pvToGo - pokemon._pvFrom) * (1.f - ratio);

    match_setLifeBarSize(lifeBar, trainerDefending);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "lifeBar animation!";
}

void match_lifebarAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //lifebar exact amount
    Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);
    auto &trainerAttackingComponent = coordinator->getComponent<Trainer>(trainerAttacking);
    auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);
    Attack attack = trainerAttackingComponent._pokemons[0]._attacks[std::get<2>(matchComponent._attacksOrder[0])];

    //reset
    auto &pokemon = trainerDefendingComponent._pokemons[0];
    pokemon._currentHP = pokemon._pvToGo;
    pokemon._pvFrom = pokemon._currentHP;

    if (trainerDefendingComponent._pokemons[0]._currentHP <= 0)
    {
        trainerDefendingComponent._pokemons[0]._currentHP = 0;
        matchComponent._timeAnimation = 2.f;
        matchComponent.setAnimation(match_faintingAnimation, match_faintingAnimationFinished);
    }
    else
    {
        matchComponent._timeAnimation = 1.f;

        //pop front
        std::vector<std::tuple<Entity, Entity, int>> newAttacksOrder;
        for (int i = 1; i < matchComponent._attacksOrder.size(); i++)
            newAttacksOrder.push_back(matchComponent._attacksOrder[i]);
        matchComponent._attacksOrder = newAttacksOrder;

        new_attackSequence(match);
    }
}

void match_flickeringAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);
    auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);
    auto &trainerDefendingSprite = coordinator->getComponent<SpriteRenderer>(trainerDefendingComponent._spriteLinked);

    trainerDefendingSprite._opacity = my_step(my_sin(matchComponent._timeAnimation * 50), 0.);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "Flickering animation!";
}

void match_flickeringAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);
    auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);
    auto &trainerDefendingSprite = coordinator->getComponent<SpriteRenderer>(trainerDefendingComponent._spriteLinked);

    trainerDefendingSprite._opacity = 1.;

    matchComponent._timeAnimation = 1.f;

    matchComponent.setAnimation(match_lifebarAnimation, match_lifebarAnimationFinished);
}


void match_attackAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
    Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);

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

    matchComponent._timeAnimation = 1.f;

    match_showPokemonInfos();
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

    match_removePokemonInfos();

    matchComponent._timeAnimation = 3.f;
    matchComponent.setAnimation(match_attackAnimation, match_attackAnimationFinished);
}


void new_attackSequence(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &trainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);

    if (matchComponent._attacksOrder.empty())
    {
        //end of the attack sequence
        match_showMain();
        matchComponent.setAnimation(nullptr, nullptr);
        std::cout << "End of the attack sequence !!!!!!" << std::endl;
    }
    else
    {
        //precalculate the attack
        Entity trainerAttacking = std::get<0>(matchComponent._attacksOrder[0]);
        Entity trainerDefending = std::get<1>(matchComponent._attacksOrder[0]);
        auto &trainerAttackingComponent = coordinator->getComponent<Trainer>(trainerAttacking);
        auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);
        Attack attack = trainerAttackingComponent._pokemons[0]._attacks[std::get<2>(matchComponent._attacksOrder[0])];

        //TODO: calculate the damage
        trainerDefendingComponent._pokemons[0]._pvFrom = trainerDefendingComponent._pokemons[0]._currentHP;
        trainerDefendingComponent._pokemons[0]._pvToGo = trainerDefendingComponent._pokemons[0]._currentHP - attack._power;

        matchComponent._timeAnimation = 1.f;
        matchComponent.setAnimation(match_startAttackAnimation, match_startAttackAnimationFinished);
    }
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

    new_attackSequence(match);
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

    match_setupCombatSequence();
}

