/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/collisionSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/ecs.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/components/boxCollider.hpp"

CollisionSystem::CollisionSystem()
{
    _signature = getCoordinator()->getComponentSignature<Transform>();
    _signature |= getCoordinator()->getComponentSignature<BoxCollider>();

    for (int i = 0; i < 240; i++)
        _chuncks.push_back(std::vector<Entity>());
}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const &entity : _entitiesThisFrame)
        coordinator->_componentManager->getComponent<BoxCollider>(entity)._entitiesCollided.clear();
    //lag : passer les calculs sur le gpu ?
    for (auto entity : _entitiesThisFrame) {
        auto& collisionBox = coordinator->_componentManager->getComponent<BoxCollider>(entity);
        auto& transform = coordinator->_componentManager->getComponent<Transform>(entity);

        if (collisionBox._chunck == -1)
            continue;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && isDebug() && !isServer()) {
            sf::VertexArray lineStrip(sf::LineStrip, 5);
            lineStrip[0].position = {transform._x + collisionBox._offsetX - collisionBox._width / 2, transform._y + collisionBox._offsetY - collisionBox._height / 2};
            lineStrip[1].position = {transform._x + collisionBox._offsetX + collisionBox._width / 2, transform._y + collisionBox._offsetY - collisionBox._height / 2};
            lineStrip[2].position = {transform._x + collisionBox._offsetX + collisionBox._width / 2, transform._y + collisionBox._offsetY + collisionBox._height / 2};
            lineStrip[3].position = {transform._x + collisionBox._offsetX - collisionBox._width / 2, transform._y + collisionBox._offsetY + collisionBox._height / 2};
            lineStrip[4].position = {transform._x + collisionBox._offsetX - collisionBox._width / 2, transform._y + collisionBox._offsetY - collisionBox._height / 2};
            lineStrip[0].color = sf::Color::Red;
            lineStrip[1].color = sf::Color::Red;
            lineStrip[2].color = sf::Color::Red;
            lineStrip[3].color = sf::Color::Red;
            lineStrip[4].color = sf::Color::Red;
            coordinator->_window->draw(lineStrip);
        }
    }
    for (int i = 0; i < _chuncks.size(); i++) {
        std::vector<Entity> entitiesNear = getAllEntitiesNear(i);
        std::vector<Entity> newEntities;
        for (auto const &entity: _chuncks[i]) {
            if (!coordinator->hasComponent<BoxCollider>(entity))
                continue;
            auto &boxCollider = coordinator->_componentManager->getComponent<BoxCollider>(entity);
            auto &transform = coordinator->_componentManager->getComponent<Transform>(entity);
            if (boxCollider._chunck != i)
                continue;
            newEntities.push_back(entity);
            for (auto const &entity2: entitiesNear) {
                if (entity == entity2)
                    continue;
                if (!coordinator->hasComponent<BoxCollider>(entity2))
                    continue;
                auto &boxCollider2 = coordinator->_componentManager->getComponent<BoxCollider>(entity2);
                auto &transform2 = coordinator->_componentManager->getComponent<Transform>(entity2);

                if (!(transform._x + boxCollider._offsetX + boxCollider._width / 2 <= transform2._x + boxCollider2._offsetX - boxCollider2._width / 2 ||
                      transform._x + boxCollider._offsetX - boxCollider._width / 2 >= transform2._x + boxCollider2._offsetX + boxCollider2._width / 2 ||
                      transform._y + boxCollider._offsetY + boxCollider._height / 2 <= transform2._y + boxCollider2._offsetY - boxCollider2._height / 2 ||
                      transform._y + boxCollider._offsetY - boxCollider._height / 2 >= transform2._y + boxCollider2._offsetY + boxCollider2._height / 2)) {
                    boxCollider._entitiesCollided.push_back(entity2);
                    boxCollider2._entitiesCollided.push_back(entity);
                }
            }
        }
        _chuncks[i] = newEntities;
    }
}

void CollisionSystem::addedEntity(Entity entity)
{
    setEntityChunck(entity);
}

void CollisionSystem::removedEntity(Entity entity)
{
    removeEntityChunck(entity);
}

void CollisionSystem::entityMoved(Entity entity)
{
    if (!getCoordinator()->hasComponent<BoxCollider>(entity))
        return;
    setEntityChunck(entity);
}

void CollisionSystem::removeEntityChunck(Entity entity)
{
    if (getCoordinator()->hasComponent<BoxCollider>(entity)) {
        auto &collisionBox = getCoordinator()->getComponent<BoxCollider>(entity);
        int currentChunck = collisionBox._chunck;

        if (currentChunck < 0 || currentChunck >= _chuncks.size())
            return;
        for (int i = 0; i < _chuncks[currentChunck].size(); i++)
            if (_chuncks[currentChunck][i] == entity) {
                _chuncks[currentChunck].erase(_chuncks[currentChunck].begin() + i);
                break;
            }
    } else {
        for (auto &chunck: _chuncks) {
            for (int i = 0; i < chunck.size(); i++)
                if (chunck[i] == entity) {
                    chunck.erase(chunck.begin() + i);
                    break;
                }
        }
    }
}

void CollisionSystem::setEntityChunck(Entity entity)
{
    auto &collisionBox = getCoordinator()->getComponent<BoxCollider>(entity);
    auto &transform = getCoordinator()->getComponent<Transform>(entity);

    int newChunckX = transform._x / 100;
    int newChunckY = transform._y / 100;
    int newChunck = newChunckX * 12 + newChunckY;

    if (newChunckX < 0 || newChunckX >= 20 || newChunckY < 0 || newChunckY >= 12) {
        if (collisionBox._chunck != -1)
            removeEntityChunck(entity);
        collisionBox._chunck = -1;
        return;
    }

    if (newChunck < 0 || newChunck >= _chuncks.size()) {
        if (collisionBox._chunck != -1)
            removeEntityChunck(entity);
        collisionBox._chunck = -1;
        return;
    }
    if (collisionBox._chunck != newChunck) {
        removeEntityChunck(entity);
        collisionBox._chunck = newChunck;
        _chuncks[newChunck].push_back(entity);
    }
}

std::vector<Entity> CollisionSystem::getAllEntitiesNear(int thisChunck)
{
    std::vector<Entity> entities;
    int currentChunck = thisChunck;

    if (currentChunck < 0 || currentChunck >= _chuncks.size())
        return entities;
    for (int j = 0; j < 3; j += 1) {
        for (int i = -13; i <= -11; i++) {
            if (currentChunck + i + j * 12 < 0 || currentChunck + i + j * 12 >= _chuncks.size())
                continue;
            if (currentChunck + i + j * 12 < currentChunck)
                continue;
            for (auto const &e: _chuncks[currentChunck + i + j * 12])
                entities.push_back(e);
        }
    }
    return entities;
}
