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
#include "../include/core/components/tag.hpp"
#include "../include/core/components/uiButton.hpp"

void new_actionSequence(Entity match);

void match_faintingAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //make the tuple
    Entity trainerAttacking = std::get<0>(matchComponent._actions[0]);
    Entity trainerDefending = std::get<1>(matchComponent._actions[0]);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    textMenuComponent._text = "Fainting animation!";
}

void match_faintingAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);


    bool pokemonAlive = false;
    for (auto &pokemon : enemyTrainerComponent._pokemons) {
        if (pokemon._id == -1)
            continue;
        std::cout << "pokemon._currentHP: " << pokemon._currentHP << std::endl;
        if (pokemon._currentHP > 0)
            pokemonAlive = true;
    }
    if (!pokemonAlive)
    {
        std::cout << "You win!" << std::endl;
    }

    new_actionSequence(match);
}

void match_lifebarAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    //make the tuple
    Entity trainerAttacking = std::get<0>(matchComponent._actions[0]);
    Entity trainerDefending = std::get<1>(matchComponent._actions[0]);
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
    Entity trainerAttacking = std::get<0>(matchComponent._actions[0]);
    Entity trainerDefending = std::get<1>(matchComponent._actions[0]);
    auto &trainerAttackingComponent = coordinator->getComponent<Trainer>(trainerAttacking);
    auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);
    Attack attack = trainerAttackingComponent._pokemons[0]._attacks[std::get<2>(matchComponent._actions[0])];

    //reset
    auto &pokemon = trainerDefendingComponent._pokemons[0];
    pokemon._currentHP = pokemon._pvToGo;
    pokemon._pvFrom = pokemon._currentHP;

    //pop front
    std::vector<std::tuple<Entity, Entity, int, int>> newAttacksOrder;
    for (int i = 1; i < matchComponent._actions.size(); i++)
        newAttacksOrder.push_back(matchComponent._actions[i]);
    matchComponent._actions = newAttacksOrder;

    if (trainerDefendingComponent._pokemons[0]._currentHP <= 0)
    {
        trainerDefendingComponent._pokemons[0]._currentHP = 0;
        matchComponent._timeAnimation = 2.f;

        newAttacksOrder.clear();
        for (int i = 0; i < matchComponent._actions.size(); i++)
            if (std::get<0>(matchComponent._actions[i]) != trainerDefending && std::get<1>(matchComponent._actions[i]) != trainerDefending)
                newAttacksOrder.push_back(matchComponent._actions[i]);
        matchComponent._actions = newAttacksOrder;

        matchComponent.setAnimation(match_faintingAnimation, match_faintingAnimationFinished);
    }
    else
    {
        matchComponent._timeAnimation = 1.f;
        new_actionSequence(match);
    }
}

void match_flickeringAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity trainerDefending = std::get<1>(matchComponent._actions[0]);
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

    Entity trainerDefending = std::get<1>(matchComponent._actions[0]);
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

    Entity trainerAttacking = std::get<0>(matchComponent._actions[0]);
    Entity trainerDefending = std::get<1>(matchComponent._actions[0]);

    auto &trainerAttackingComponent = coordinator->getComponent<Trainer>(trainerAttacking);
    auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);

    Entity textMenu = coordinator->getEntityFromTag("textMenu");
    auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
    Attack attack = trainerAttackingComponent._pokemons[0]._attacks[std::get<3>(matchComponent._actions[0])];
    textMenuComponent._text = trainerAttackingComponent._name + " attacks " + trainerDefendingComponent._name + " With " + attack._name + "!";
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


void new_actionSequence(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &trainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);

    if (matchComponent._actions.empty())
    {
        //end of the attack sequence
        match_showMain();
        matchComponent.setAnimation(nullptr, nullptr);
        Entity textMenu = coordinator->getEntityFromTag("textMenu");
        auto &textMenuComponent = coordinator->getComponent<Text>(textMenu);
        textMenuComponent._text = "";
        std::cout << "End of the attack sequence !!!!!!" << std::endl;

        matchComponent.enemyPokemonAction();
    }
    else
    {
        //precalculate the attack
        Entity trainerAttacking = std::get<0>(matchComponent._actions[0]);
        Entity trainerDefending = std::get<1>(matchComponent._actions[0]);
        auto &trainerAttackingComponent = coordinator->getComponent<Trainer>(trainerAttacking);
        auto &trainerDefendingComponent = coordinator->getComponent<Trainer>(trainerDefending);
        Attack attack = trainerAttackingComponent._pokemons[0]._attacks[std::get<3>(matchComponent._actions[0])];

        //TODO: calculate the damage
        trainerDefendingComponent._pokemons[0]._pvFrom = trainerDefendingComponent._pokemons[0]._currentHP;
        trainerDefendingComponent._pokemons[0]._pvToGo = trainerDefendingComponent._pokemons[0]._currentHP - attack._power;

        matchComponent._timeAnimation = 1.f;
        matchComponent.setAnimation(match_startAttackAnimation, match_startAttackAnimationFinished);
    }
}

bool action_priority(std::tuple<Entity, Entity, int , int> action1, std::tuple<Entity, Entity, int , int> action2)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &trainer1 = coordinator->getComponent<Trainer>(std::get<0>(action1));
    auto &trainer2 = coordinator->getComponent<Trainer>(std::get<0>(action2));
    auto &action_type1 = std::get<2>(action1);
    auto &action_type2 = std::get<2>(action2);

    if (action_type1 != MATCH_ACTION_ATTACK && action_type2 == MATCH_ACTION_ATTACK)
        return true;
    if (action_type2 != MATCH_ACTION_ATTACK && action_type1 == MATCH_ACTION_ATTACK)
        return false;
    return trainer1._pokemons[0]._currentSpeed > trainer2._pokemons[0]._currentSpeed;
}

void match_setupCombatSequence()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");

    auto &matchComponent = coordinator->getComponent<Match>(match);

    std::vector<Entity> entities = coordinator->getEntitiesFromTag("attack");
    for (auto &entity : entities)
        coordinator->killEntity(entity);

    matchComponent._actions.clear();
    std::vector<std::tuple<Entity, Entity, int , int>> newActions;

    while (!matchComponent._actionsInQueue.empty()) {
        auto frontAction = matchComponent._actionsInQueue[0];

        for (int i = 1; i < matchComponent._actionsInQueue.size(); i++)
        {
            auto action = matchComponent._actionsInQueue[i];
            if (action_priority(action, frontAction))
                frontAction = action;
        }
        for (auto & action : matchComponent._actionsInQueue) {
            if (action != frontAction)
                newActions.push_back(action);
        }

        matchComponent._actions.push_back(frontAction);
        matchComponent._actionsInQueue = newActions;
        newActions.clear();
    }
    matchComponent._actionsInQueue.clear();

    new_actionSequence(match);
}


void match_launchAttack(Entity self)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");

    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &trainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);
    auto &uiButtonComponent = coordinator->getComponent<UiButton>(self);

    std::vector<Entity> entities = coordinator->getEntitiesFromTag("attack");
    for (auto &entity : entities)
        coordinator->killEntity(entity);
    std::tuple<Entity, Entity, int , int> attack = std::make_tuple(matchComponent._trainersPlayer[0], matchComponent._trainersOpponent[0], MATCH_ACTION_ATTACK, uiButtonComponent._id);
    matchComponent._actionsInQueue.push_back(attack);
}

