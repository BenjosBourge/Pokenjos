/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/playerMovementSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/playerController.hpp"
#include "../../../../include/core/components/transform.hpp"

PlayerMovementSystem::PlayerMovementSystem()
{
    _signature = getCoordinator()->getComponentSignature<Transform>();
    _signature |= getCoordinator()->getComponentSignature<PlayerController>();
}

PlayerMovementSystem::~PlayerMovementSystem()
{

}

void PlayerMovementSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const& entity : _entitiesThisFrame) {
        auto &playerController = coordinator->getComponent<PlayerController>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            transform._y -= 100 * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            transform._y += 100 * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            transform._x -= 100 * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            transform._x += 100 * deltaTime;
        }
    }
}

void PlayerMovementSystem::addedEntity(Entity entity)
{

}

void PlayerMovementSystem::removedEntity(Entity entity)
{

}