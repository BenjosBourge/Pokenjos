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
#include "../include/core/components/camera.hpp"
#include "../include/components/playerController.hpp"
#include "../include/prefabPokemon.hpp"
#include "../include/components/match.hpp"
#include "../include/components/trainer.hpp"
#include "../include/core/components/ui.hpp"
#include "../include/core/components/uiButton.hpp"
#include "../include/core/components/boxCollider.hpp"
#include "../include/core/components/interactionBoxCollider.hpp"

bool isDebug()
{
    return true;
}

void createCamera(std::shared_ptr<Coordinator> coordinator)
{
    Entity camera = coordinator->createEntity();

    coordinator->addComponent<Transform>(camera, Transform(1920/2, 1080/2, 1, 1));
    coordinator->addComponent<Camera>(camera);
    coordinator->addComponent<Tag>(camera, Tag("camera"));
}

void createPlayer(std::shared_ptr<Coordinator> coordinator)
{
    Entity player = coordinator->createEntity();

    coordinator->addComponent<Transform>(player, Transform(10 * 48 + 24, 10 * 48 + 24, 1, 1));
    coordinator->addComponent<SpriteRenderer>(player, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 1));
    coordinator->addComponent<Tag>(player, Tag("player"));
    coordinator->addComponent<PlayerController>(player);
    auto &playerSprite = coordinator->getComponent<SpriteRenderer>(player);
    playerSprite._color = sf::Color(255, 0, 0);
}

void createMap(std::shared_ptr<Coordinator> coordinator)
{
    for (int i = 0; i < 30; i += 1)
        for (int j = 0; j < 30; j += 1) {
            Entity tile = coordinator->createEntity();
            coordinator->addComponent<Transform>(tile, Transform(i * 48 + 24, j * 48 + 24, 1, 1));
            coordinator->addComponent<SpriteRenderer>(tile, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 46, 46));
            coordinator->addComponent<Tag>(tile, Tag("tile"));
        }
}

void printPokemon(Pokemon pokemon)
{
    std::cout << "Pokemon: " << pokemon._name << std::endl;
    std::cout << "Level: " << pokemon._level << std::endl;
    std::cout << "HP: " << pokemon._currentHP << "/" << pokemon._currentMaxHP << std::endl;

    std::cout << "Attack: " << pokemon._currentAttack << std::endl;
    std::cout << "Defense: " << pokemon._currentDefense << std::endl;
    std::cout << "Special Attack: " << pokemon._currentSpecialAttack << std::endl;
    std::cout << "Special Defense: " << pokemon._currentSpecialDefense << std::endl;
    std::cout << "Speed: " << pokemon._currentSpeed << std::endl;

    std::cout << "Type1: " << pokemon._type1 << std::endl;
    std::cout << "Type2: " << pokemon._type2 << std::endl;

    for (int i = 0; i < 4; i += 1) {
        std::cout << "Attack: " << pokemon._attacks[i]._name << std::endl;
    }
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

void match_attackAnimation(Entity match, float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    //put here animation for attack
}

void match_showAttacks(Entity match);

void match_attackAnimationFinished(Entity match)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &matchComponent = coordinator->getComponent<Match>(match);

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

    match_showAttacks(match);
}

int main()
{
    srand(time(nullptr));
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    createCamera(coordinator);


    //put here your code to instanciate entities
    //createMap(coordinator);
    //createPlayer(coordinator);


    Entity match = coordinator->createEntity();
    coordinator->addComponent<Match>(match);
    auto &matchComponent = coordinator->getComponent<Match>(match);
    matchComponent.setSelfEntity(match);
    coordinator->addComponent<Tag>(match, Tag("match"));

    Entity trainer = coordinator->createEntity();
    coordinator->addComponent<Trainer>(trainer);
    auto &trainerComponent = coordinator->getComponent<Trainer>(trainer);
    trainerComponent._name = "Benjamin";
    trainerComponent._money = 1000;

    Pokemon pokemon = createPokemon(BULBASAUR, 5);
    trainerComponent._pokemons[0] = pokemon;


    Entity enemyTrainer = coordinator->createEntity();
    coordinator->addComponent<Trainer>(enemyTrainer);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(enemyTrainer);
    enemyTrainerComponent._name = "Julien";
    enemyTrainerComponent._money = 1000;

    Pokemon enemyPokemon = createPokemon(CHARMANDER, 5);
    enemyTrainerComponent._pokemons[0] = enemyPokemon;


    Entity playerSprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerSprite, Transform(1920/2, 1080/2 - 100, 5, 5));
    coordinator->addComponent<SpriteRenderer>(playerSprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 1));
    coordinator->addComponent<Tag>(playerSprite, Tag("playerSprite"));

    Entity enemySprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemySprite, Transform(1920/2, 1080/2 - 250, 5, 5));
    coordinator->addComponent<SpriteRenderer>(enemySprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 1));
    coordinator->addComponent<Tag>(enemySprite, Tag("enemySprite"));

    matchComponent._spritePlayer = playerSprite;
    matchComponent._spriteOpponent = enemySprite;

    matchComponent.setAnimation(match_startAnimation, match_startAnimationFinished);
    matchComponent.launchNewMatch({trainer}, {enemyTrainer});

    Entity MenuSprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(MenuSprite, Transform(1920/2, 1080/2 + 355, 62, 16));
    coordinator->addComponent<SpriteRenderer>(MenuSprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 3));
    auto &MenuSpriteComponent = coordinator->getComponent<SpriteRenderer>(MenuSprite);
    MenuSpriteComponent._color = sf::Color(150, 150, 150);




    if (serverRunning())
        return 0;

    int fps = 60;
    float timerFps = 0;
    while (coordinator->_window->isOpen()) {
        sf::Event event;
        while (coordinator->_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                coordinator->_window->close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            coordinator->_window->close();
            break;
        }
        coordinator->_window->clear();
        coordinator->update();
        if (isDebug()) {
            fps++;
            timerFps += coordinator->_deltaTime;
            if (timerFps >= 1) {
                if (fps < 50)
                    std::cerr << "Low fps, Cause:" << coordinator->_highConsumingSystem << " with " << coordinator->_highConsumingTime << "ms per frame" << std::endl;
                std::cout << "FPS: " << fps << std::endl;
                fps = 0;
                timerFps = 0;
                //coordinator->_networkManager->_clock.restart();
                //coordinator->_networkManager->sendPacket(coordinator->_networkManager->makePacket(CMD_PING, {}));
            }
        }
        coordinator->_window->display();
    }

    return 0;
}