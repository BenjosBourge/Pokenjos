/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/interactionCollisionSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/ecs.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/components/interactionBoxCollider.hpp"

InteractionCollisionSystem::InteractionCollisionSystem()
{
    _signature = getCoordinator()->getComponentSignature<Transform>();
    _signature |= getCoordinator()->getComponentSignature<InteractionBoxCollider>();
}

InteractionCollisionSystem::~InteractionCollisionSystem()
{

}

void InteractionCollisionSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const &entity : _entitiesThisFrame)
        coordinator->_componentManager->getComponent<InteractionBoxCollider>(entity)._entitiesCollided.clear();
    //lag : passer les calculs sur le gpu ?
    for (int i = 0; i < _entities.size(); i++) {
        auto const& entity = _entities[i];
        auto& collisionBox = coordinator->_componentManager->getComponent<InteractionBoxCollider>(entity);
        auto& transform = coordinator->_componentManager->getComponent<Transform>(entity);

        for (int j = 0; j < _entitiesTrigger.size(); j++) {
            auto const& entity2 = _entitiesTrigger[j];
            if (entity == entity2)
                continue;
            auto& collisionBox2 = coordinator->_componentManager->getComponent<InteractionBoxCollider>(entity2);
            auto& transform2 = coordinator->_componentManager->getComponent<Transform>(entity2);

            if (!(transform._x + collisionBox._offsetX + collisionBox._width / 2 <= transform2._x + collisionBox2._offsetX - collisionBox2._width / 2 ||
                    transform._x + collisionBox._offsetX - collisionBox._width / 2 >= transform2._x + collisionBox2._offsetX + collisionBox2._width / 2 ||
                    transform._y + collisionBox._offsetY + collisionBox._height / 2 <= transform2._y + collisionBox2._offsetY - collisionBox2._height / 2 ||
                    transform._y + collisionBox._offsetY - collisionBox._height / 2 >= transform2._y + collisionBox2._offsetY + collisionBox2._height / 2)) {
                collisionBox._entitiesCollided.push_back(entity2);
                collisionBox2._entitiesCollided.push_back(entity);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && isDebug() && !isServer()) {
            sf::VertexArray lineStrip(sf::LineStrip, 5);
            lineStrip[0].position = {transform._x + collisionBox._offsetX - collisionBox._width / 2, transform._y + collisionBox._offsetY - collisionBox._height / 2};
            lineStrip[1].position = {transform._x + collisionBox._offsetX + collisionBox._width / 2, transform._y + collisionBox._offsetY - collisionBox._height / 2};
            lineStrip[2].position = {transform._x + collisionBox._offsetX + collisionBox._width / 2, transform._y + collisionBox._offsetY + collisionBox._height / 2};
            lineStrip[3].position = {transform._x + collisionBox._offsetX - collisionBox._width / 2, transform._y + collisionBox._offsetY + collisionBox._height / 2};
            lineStrip[4].position = {transform._x + collisionBox._offsetX - collisionBox._width / 2, transform._y + collisionBox._offsetY - collisionBox._height / 2};
            lineStrip[0].color = sf::Color::Green;
            lineStrip[1].color = sf::Color::Green;
            lineStrip[2].color = sf::Color::Green;
            lineStrip[3].color = sf::Color::Green;
            lineStrip[4].color = sf::Color::Green;
            coordinator->_window->draw(lineStrip);
        }
    }
}

void InteractionCollisionSystem::addedEntity(Entity entity)
{
    if (getCoordinator()->getComponent<InteractionBoxCollider>(entity)._isTrigger)
        _entitiesTrigger.push_back(entity);
}

void InteractionCollisionSystem::removedEntity(Entity entity)
{
    std::vector<Entity> newEntityTrigger;

    for (auto const& entityTrigger : _entitiesTrigger) {
        if (entityTrigger != entity)
            newEntityTrigger.push_back(entityTrigger);
    }
    _entitiesTrigger = newEntityTrigger;
}