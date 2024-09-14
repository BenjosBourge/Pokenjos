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

        if (!playerController._isMoving) {
            int x = playerController._tileX;
            int y = playerController._tileY;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                playerController._tileY -= 1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                playerController._tileY += 1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                playerController._tileX -= 1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                playerController._tileX += 1;

            if (playerController._tileX != x || playerController._tileY != y) {
                playerController._isMoving = true;
                playerController._initialTileX = x;
                playerController._initialTileY = y;
                transform._x = x * 48 + 24;
                transform._y = y * 48 + 24;
                playerController._timerMove = 0.3f;
            }
        } else {
            sf::Vector2f initialPosition = sf::Vector2f(playerController._initialTileX * 48 + 24, playerController._initialTileY * 48 + 24);
            sf::Vector2f finalPosition = sf::Vector2f(playerController._tileX * 48 + 24, playerController._tileY * 48 + 24);
            sf::Vector2f direction = finalPosition - initialPosition;
            playerController._timerMove -= deltaTime;
            transform._x = initialPosition.x + direction.x * (0.3f - playerController._timerMove) / 0.3f;
            transform._y = initialPosition.y + direction.y * (0.3f - playerController._timerMove) / 0.3f;

            if (playerController._timerMove <= 0) {
                playerController._isMoving = false;
                transform._x = finalPosition.x;
                transform._y = finalPosition.y;
            }
        }
    }
}

void PlayerMovementSystem::addedEntity(Entity entity)
{

}

void PlayerMovementSystem::removedEntity(Entity entity)
{

}