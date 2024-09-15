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
    createMap(coordinator);
    createPlayer(coordinator);

    Pokemon pokemon = createPokemon(BULBASAUR, 1);
    printPokemon(pokemon);


    for (int i = 0; i < 10; i += 1) {
        pokemon.gainXP(10000);
        std::cout << std::endl << "Gained 10000 XP" << std::endl;
        printPokemon(pokemon);
    }


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
                //std::cout << fps << std::endl;
                if (fps < 50)
                    std::cerr << "Low fps, Cause:" << coordinator->_highConsumingSystem << " with " << coordinator->_highConsumingTime << "ms per frame" << std::endl;
                //std::cout << "FPS: " << fps << std::endl;
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