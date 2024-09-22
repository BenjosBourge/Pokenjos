/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include <vector>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "../include/core/coordinator.hpp"
#include "../include/core/ecs.hpp"
#include "../include/core/texture.hpp"
#include "../include/core/components/transform.hpp"
#include "../include/core/components/spriteRenderer.hpp"
#include "../include/core/components/tag.hpp"
#include "../include/prefabPokemon.hpp"
#include "../include/components/match.hpp"
#include "../include/components/trainer.hpp"
#include "../include/core/components/ui.hpp"
#include "../include/core/components/uiButton.hpp"
#include "../include/core/components/interactionBoxCollider.hpp"
#include "../include/matchMethods.hpp"
#include "../include/core/components/text.hpp"
#include "../include/core/components/child.hpp"

void match_setLifeBarSize(Entity lifeBar, Entity trainer)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");
    auto &matchComponent = coordinator->getComponent<Match>(match);

    auto &lifeBarComponent = coordinator->getComponent<Transform>(lifeBar);
    Pokemon pokemon = coordinator->getComponent<Trainer>(trainer)._pokemons[0];

    lifeBarComponent._width = 8.f * ((float)pokemon._currentHP / (float)pokemon._currentMaxHP);
    lifeBarComponent._height = 0.4;
    lifeBarComponent._x = 60.f - (8.f - lifeBarComponent._width) * 0.5f * 32.f;
    lifeBarComponent._y = 30.f;
    auto &lifeBarChild = coordinator->getComponent<Child>(lifeBar);
    auto &parentTransform = coordinator->getComponent<Transform>(lifeBarChild._parent);

    lifeBarChild._xOffset = lifeBarComponent._x;
    lifeBarChild._yOffset = lifeBarComponent._y;
    lifeBarChild._ratioScale = {lifeBarComponent._width / parentTransform._width, lifeBarComponent._height / parentTransform._height};
}

void match_showPokemonInfos()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");
    auto &matchComponent = coordinator->getComponent<Match>(match);

    /*Enemy Pokemon*/
    float pix = -50;
    float piy = -450;

    Entity InfoEnemy = coordinator->createEntity();
    coordinator->addComponent<Transform>(InfoEnemy, Transform(pix, piy, 18, 4));
    coordinator->addComponent<SpriteRenderer>(InfoEnemy, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    coordinator->addComponent<Tag>(InfoEnemy, Tag("InfoEnemy"));

    int lifeBarX = 60;
    int lifeBarY = 30;
    Entity lifeBarEnemy = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarEnemy, Transform(lifeBarX, lifeBarY, 8, 0.4));
    coordinator->addComponent<SpriteRenderer>(lifeBarEnemy, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 3));
    auto &lifeBarEnemySprite = coordinator->getComponent<SpriteRenderer>(lifeBarEnemy);
    lifeBarEnemySprite._color = sf::Color(0, 255, 0);
    coordinator->addComponent<Tag>(lifeBarEnemy, Tag("lifebar_1"));
    coordinator->addComponent<Child>(lifeBarEnemy, Child(InfoEnemy, lifeBarEnemy));
    match_setLifeBarSize(lifeBarEnemy, matchComponent._trainersOpponent[0]);

    Entity lifeBarEnemyBackground = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarEnemyBackground, Transform(lifeBarX, lifeBarY, 8.2, 0.6));
    coordinator->addComponent<SpriteRenderer>(lifeBarEnemyBackground, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    auto &lifeBarEnemyBackgroundSprite = coordinator->getComponent<SpriteRenderer>(lifeBarEnemyBackground);
    lifeBarEnemyBackgroundSprite._color = sf::Color(0, 0, 0);
    coordinator->addComponent<Tag>(lifeBarEnemyBackground, Tag("InfoEnemy_sub"));
    coordinator->addComponent<Child>(lifeBarEnemyBackground, Child(InfoEnemy, lifeBarEnemyBackground));

    Entity enemyName = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemyName, Transform(-250, -60, 18, 4));
    coordinator->addComponent<Text>(enemyName, Text("Enemy", 48));
    coordinator->addComponent<Tag>(enemyName, Tag("InfoEnemy_sub"));
    coordinator->addComponent<UserInterface>(enemyName);
    coordinator->addComponent<Child>(enemyName, Child(InfoEnemy, enemyName));
    auto &enemyNameText = coordinator->getComponent<Text>(enemyName);
    enemyNameText._color = sf::Color(0, 0, 0);
    auto &enemyTrainer = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);
    enemyNameText._text = enemyTrainer._pokemons[0]._name;

    Entity enemyLevel = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemyLevel, Transform(150, -60, 18, 4));
    coordinator->addComponent<Text>(enemyLevel, Text("Lvl:", 40));
    coordinator->addComponent<Tag>(enemyLevel, Tag("InfoEnemy_sub"));
    coordinator->addComponent<UserInterface>(enemyLevel);
    coordinator->addComponent<Child>(enemyLevel, Child(InfoEnemy, enemyLevel));
    auto &enemyLevelText = coordinator->getComponent<Text>(enemyLevel);
    enemyLevelText._color = sf::Color(0, 0, 0);
    enemyLevelText._text += std::to_string(enemyTrainer._pokemons[0]._level);



    /*Player Pokemon*/

    pix = 180;
    piy = 10;

    Entity InfoPlayer = coordinator->createEntity();
    coordinator->addComponent<Transform>(InfoPlayer, Transform(pix, piy, 18, 4));
    coordinator->addComponent<SpriteRenderer>(InfoPlayer, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    coordinator->addComponent<Tag>(InfoPlayer, Tag("InfoPlayer"));

    lifeBarX = 60;
    lifeBarY = 30;
    Entity lifeBarPlayer = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarPlayer, Transform(lifeBarX, lifeBarY, 8, 0.4));
    coordinator->addComponent<SpriteRenderer>(lifeBarPlayer, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 3));
    coordinator->addComponent<Child>(lifeBarPlayer, Child(InfoPlayer, lifeBarPlayer));
    auto &lifeBarPlayerSprite = coordinator->getComponent<SpriteRenderer>(lifeBarPlayer);
    lifeBarPlayerSprite._color = sf::Color(0, 255, 0);
    coordinator->addComponent<Tag>(lifeBarPlayer, Tag("lifebar_0"));
    match_setLifeBarSize(lifeBarPlayer, matchComponent._trainersPlayer[0]);

    Entity lifeBarPlayerBackground = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarPlayerBackground, Transform(lifeBarX, lifeBarY, 8.2, 0.6));
    coordinator->addComponent<SpriteRenderer>(lifeBarPlayerBackground, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    coordinator->addComponent<Child>(lifeBarPlayerBackground, Child(InfoPlayer, lifeBarPlayerBackground));
    auto &lifeBarPlayerBackgroundSprite = coordinator->getComponent<SpriteRenderer>(lifeBarPlayerBackground);
    lifeBarPlayerBackgroundSprite._color = sf::Color(0, 0, 0);
    coordinator->addComponent<Tag>(lifeBarPlayerBackground, Tag("InfoPlayer_sub"));

    Entity playerName = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerName, Transform(-250, -60, 18, 4));
    coordinator->addComponent<Text>(playerName, Text("Player", 48));
    coordinator->addComponent<Tag>(playerName, Tag("InfoPlayer_sub"));
    coordinator->addComponent<UserInterface>(playerName);
    coordinator->addComponent<Child>(playerName, Child(InfoPlayer, playerName));
    auto &playerNameText = coordinator->getComponent<Text>(playerName);
    playerNameText._color = sf::Color(0, 0, 0);
    auto &playerTrainer = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    playerNameText._text = playerTrainer._pokemons[0]._name;

    Entity playerLevel = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerLevel, Transform(150, -60, 18, 4));
    coordinator->addComponent<Text>(playerLevel, Text("Lvl:", 40));
    coordinator->addComponent<Tag>(playerLevel, Tag("InfoPlayer_sub"));
    coordinator->addComponent<UserInterface>(playerLevel);
    coordinator->addComponent<Child>(playerLevel, Child(InfoPlayer, playerLevel));
    auto &playerLevelText = coordinator->getComponent<Text>(playerLevel);
    playerLevelText._color = sf::Color(0, 0, 0);
    playerLevelText._text += std::to_string(playerTrainer._pokemons[0]._level);
}

void match_removePokemonInfos()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    std::vector<Entity> entities = coordinator->getEntitiesFromTag("InfoPlayer");
    for (auto &entity : entities)
        coordinator->killEntity(entity);

    entities = coordinator->getEntitiesFromTag("InfoEnemy");
    for (auto &entity : entities)
        coordinator->killEntity(entity);
}

void match_showAttacks(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);
    auto &trainerComponent = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);

    for (int i = 0; i < 4; i += 1) {
        auto attack = trainerComponent._pokemons[0]._attacks[i];

        if (attack._id == -1)
            break;

        std::cout << i << ": " << attack._name << std::endl;

        Entity attackEntity = coordinator->createEntity();
        int x = -480 + 960 * (i%2);
        int y = 225 + 200 * (i/2);

        coordinator->addComponent<Transform>(attackEntity, Transform(x, y, 29.4, 5.8));
        coordinator->addComponent<SpriteRenderer>(attackEntity, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 4));
        coordinator->addComponent<Tag>(attackEntity, Tag("attack"));
        coordinator->addComponent<UserInterface>(attackEntity);
        coordinator->addComponent<UiButton>(attackEntity, UiButton(match_launchAttack));
        auto &uiButton = coordinator->getComponent<UiButton>(attackEntity);
        uiButton.setZoomWhenHovered(true, coordinator->getComponent<Transform>(attackEntity));
        coordinator->addComponent<InteractionBoxCollider>(attackEntity, InteractionBoxCollider(29.4 * 32, 5.8 * 32, 0, 0, true));
    }
}

void match_encounterAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity playerSprite = matchComponent._spritePlayer;
    Entity enemySprite = matchComponent._spriteOpponent;
    Entity playerSpriteBase = matchComponent._spritePlayerBase;
    Entity enemySpriteBase = matchComponent._spriteOpponentBase;

    auto &playerSpriteTransform = coordinator->getComponent<Transform>(playerSprite);
    auto &enemySpriteTransform = coordinator->getComponent<Transform>(enemySprite);
    auto &playerSpriteBaseTransform = coordinator->getComponent<Transform>(playerSpriteBase);
    auto &enemySpriteBaseTransform = coordinator->getComponent<Transform>(enemySpriteBase);

    float progression = matchComponent._timeAnimation / 2.0f;
    playerSpriteTransform._x = -400 - 800 * progression;
    enemySpriteTransform._x = 400 + 800 * progression;
    playerSpriteBaseTransform._x = -400 - 800 * progression;
    enemySpriteBaseTransform._x = 400 + 800 * progression;
}


void match_encounterAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    match_showPokemonInfos();
    match_showAttacks(match);
}
