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

void match_showPokemonInfos()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");
    auto &matchComponent = coordinator->getComponent<Match>(match);

    /*Enemy Pokemon*/

    Entity InfoEnemy = coordinator->createEntity();
    coordinator->addComponent<Transform>(InfoEnemy, Transform(1920/2 - 50, 1080/2 - 450, 18, 4));
    coordinator->addComponent<SpriteRenderer>(InfoEnemy, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    coordinator->addComponent<Tag>(InfoEnemy, Tag("InfoEnemy"));

    int lifeBarX = 1920/2 + 40;
    int lifeBarY = 1080/2 - 420;
    Entity lifeBarEnemy = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarEnemy, Transform(lifeBarX, lifeBarY, 8, 0.4));
    coordinator->addComponent<SpriteRenderer>(lifeBarEnemy, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 3));
    auto &lifeBarEnemySprite = coordinator->getComponent<SpriteRenderer>(lifeBarEnemy);
    lifeBarEnemySprite._color = sf::Color(0, 255, 0);
    coordinator->addComponent<Tag>(lifeBarEnemy, Tag("InfoEnemy"));

    Entity lifeBarEnemyBackground = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarEnemyBackground, Transform(lifeBarX, lifeBarY, 8.2, 0.6));
    coordinator->addComponent<SpriteRenderer>(lifeBarEnemyBackground, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    auto &lifeBarEnemyBackgroundSprite = coordinator->getComponent<SpriteRenderer>(lifeBarEnemyBackground);
    lifeBarEnemyBackgroundSprite._color = sf::Color(0, 0, 0);
    coordinator->addComponent<Tag>(lifeBarEnemyBackground, Tag("InfoEnemy"));

    Entity enemyName = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemyName, Transform(1920/2 - 300, 1080/2 - 510, 18, 4));
    coordinator->addComponent<Text>(enemyName, Text("Enemy", 48));
    coordinator->addComponent<Tag>(enemyName, Tag("InfoEnemy"));
    coordinator->addComponent<UserInterface>(enemyName);
    auto &enemyNameText = coordinator->getComponent<Text>(enemyName);
    enemyNameText._color = sf::Color(0, 0, 0);
    auto &enemyTrainer = coordinator->getComponent<Trainer>(matchComponent._trainersOpponent[0]);
    enemyNameText._text = enemyTrainer._pokemons[0]._name;

    Entity enemyLevel = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemyLevel, Transform(1920/2 + 100, 1080/2 - 510, 18, 4));
    coordinator->addComponent<Text>(enemyLevel, Text("Lvl:", 40));
    coordinator->addComponent<Tag>(enemyLevel, Tag("InfoEnemy"));
    coordinator->addComponent<UserInterface>(enemyLevel);
    auto &enemyLevelText = coordinator->getComponent<Text>(enemyLevel);
    enemyLevelText._color = sf::Color(0, 0, 0);
    enemyLevelText._text += std::to_string(enemyTrainer._pokemons[0]._level);



    /*Player Pokemon*/

    Entity InfoPlayer = coordinator->createEntity();
    coordinator->addComponent<Transform>(InfoPlayer, Transform(1920/2 + 180, 1080/2 + 10, 18, 4));
    coordinator->addComponent<SpriteRenderer>(InfoPlayer, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    coordinator->addComponent<Tag>(InfoPlayer, Tag("InfoPlayer"));

    lifeBarX = 1920/2 + 270;
    lifeBarY = 1080/2 + 40;
    Entity lifeBarPlayer = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarPlayer, Transform(lifeBarX, lifeBarY, 8, 0.4));
    coordinator->addComponent<SpriteRenderer>(lifeBarPlayer, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 3));
    auto &lifeBarPlayerSprite = coordinator->getComponent<SpriteRenderer>(lifeBarPlayer);
    lifeBarPlayerSprite._color = sf::Color(0, 255, 0);
    coordinator->addComponent<Tag>(lifeBarPlayer, Tag("InfoPlayer"));

    Entity lifeBarPlayerBackground = coordinator->createEntity();
    coordinator->addComponent<Transform>(lifeBarPlayerBackground, Transform(lifeBarX, lifeBarY, 8.2, 0.6));
    coordinator->addComponent<SpriteRenderer>(lifeBarPlayerBackground, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 2));
    auto &lifeBarPlayerBackgroundSprite = coordinator->getComponent<SpriteRenderer>(lifeBarPlayerBackground);
    lifeBarPlayerBackgroundSprite._color = sf::Color(0, 0, 0);
    coordinator->addComponent<Tag>(lifeBarPlayerBackground, Tag("InfoPlayer"));

    Entity playerName = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerName, Transform(1920/2 - 80, 1080/2 - 50, 18, 4));
    coordinator->addComponent<Text>(playerName, Text("Player", 48));
    coordinator->addComponent<Tag>(playerName, Tag("InfoPlayer"));
    coordinator->addComponent<UserInterface>(playerName);
    auto &playerNameText = coordinator->getComponent<Text>(playerName);
    playerNameText._color = sf::Color(0, 0, 0);
    auto &playerTrainer = coordinator->getComponent<Trainer>(matchComponent._trainersPlayer[0]);
    playerNameText._text = playerTrainer._pokemons[0]._name;

    Entity playerLevel = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerLevel, Transform(1920/2 + 240, 1080/2 - 50, 18, 4));
    coordinator->addComponent<Text>(playerLevel, Text("Lvl:", 40));
    coordinator->addComponent<Tag>(playerLevel, Tag("InfoPlayer"));
    coordinator->addComponent<UserInterface>(playerLevel);
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

void match_startAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity playerSprite = matchComponent._spritePlayer;
    Entity enemySprite = matchComponent._spriteOpponent;

    auto &playerSpriteTransform = coordinator->getComponent<Transform>(playerSprite);
    auto &enemySpriteTransform = coordinator->getComponent<Transform>(enemySprite);

    float progression = matchComponent._timeAnimation / 2.0f;
    playerSpriteTransform._x = 1920/2 - 400 - 800 * progression;
    enemySpriteTransform._x = 1920/2 + 400 + 800 * progression;
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
        int x = 1920/2 - 480 + 960 * (i%2);
        int y = 1080/2 + 225 + 200 * (i/2);

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

void match_startAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

    match_showPokemonInfos();
    match_showAttacks(match);
}
