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
#include "../include/matchMethods.hpp"
#include "../include/core/components/text.hpp"

bool isDebug()
{
    return true;
}

void createCamera(std::shared_ptr<Coordinator> coordinator)
{
    Entity camera = coordinator->createEntity();

    coordinator->addComponent<Transform>(camera, Transform(0, 0, 1, 1));
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
    trainerComponent._id = 0;
    trainerComponent._pokemons[0] = createPokemon(CHARIZARD, 100);


    Entity enemyTrainer = coordinator->createEntity();
    coordinator->addComponent<Trainer>(enemyTrainer);
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(enemyTrainer);
    enemyTrainerComponent._name = "Julien";
    enemyTrainerComponent._money = 1000;
    enemyTrainerComponent._id = 1;
    enemyTrainerComponent._pokemons[0] = createPokemon(BLASTOISE, 100);


    Entity playerSprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerSprite, Transform(0, -100, 5, 5));
    coordinator->addComponent<SpriteRenderer>(playerSprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 1));
    coordinator->addComponent<Tag>(playerSprite, Tag("playerSprite"));

    Entity playerSpriteBase = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerSpriteBase, Transform(0, 40, 5, 5));
    coordinator->addComponent<SpriteRenderer>(playerSpriteBase, SpriteRenderer(TEXTURE_TYPE_PLAYER_BASE, 204, 30, 0));
    coordinator->addComponent<Tag>(playerSpriteBase, Tag("playerSpriteBase"));

    Entity enemySprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemySprite, Transform(0, -250, 5, 5));
    coordinator->addComponent<SpriteRenderer>(enemySprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 1));
    coordinator->addComponent<Tag>(enemySprite, Tag("enemySprite"));

    Entity enemySpriteBase = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemySpriteBase, Transform(0, -110, 5, 5));
    coordinator->addComponent<SpriteRenderer>(enemySpriteBase, SpriteRenderer(TEXTURE_TYPE_ENEMY_BASE, 126, 32, 0));
    coordinator->addComponent<Tag>(enemySpriteBase, Tag("enemySpriteBase"));

    matchComponent._spritePlayer = playerSprite;
    matchComponent._spriteOpponent = enemySprite;
    matchComponent._spritePlayerBase = playerSpriteBase;
    matchComponent._spriteOpponentBase = enemySpriteBase;

    matchComponent.setAnimation(match_startAnimation, match_startAnimationFinished);
    matchComponent.launchNewMatch({trainer}, {enemyTrainer});

    Entity MenuSprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(MenuSprite, Transform(0, 355, 62, 16));
    coordinator->addComponent<SpriteRenderer>(MenuSprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 3));
    auto &MenuSpriteComponent = coordinator->getComponent<SpriteRenderer>(MenuSprite);
    MenuSpriteComponent._color = sf::Color(150, 150, 150);

    Entity TextMenu = coordinator->createEntity();
    coordinator->addComponent<Transform>(TextMenu, Transform(-400, 250, 62, 16));
    coordinator->addComponent<UserInterface>(TextMenu);
    coordinator->addComponent<Tag>(TextMenu, Tag("textMenu"));
    coordinator->addComponent<Text>(TextMenu, Text("", 64, sf::Color::White));




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