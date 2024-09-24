/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/coordinator.hpp"
#include "../../include/core/systems/childSystem.hpp"
#include "../../include/core/components/child.hpp"
#include "../../include/core/components/tag.hpp"

Coordinator::Coordinator()
{

    initWindow();
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>();
    _networkManager = std::make_shared<NetworkManager>();

    /*
     * Debug
     * */
    _highConsumingSystem = "";
    _highConsumingTime = 0;
}

Coordinator::~Coordinator()
{

}

void Coordinator::init()
{
    loadTextures();
    _entityManager->_componentManager = _componentManager;
    _componentManager->_entityManager = _entityManager;
    _systemManager->_entityManager = _entityManager;
    _systemManager->_componentManager = _componentManager;
    _componentManager->init();
    _systemManager->init();
}

void Coordinator::update()
{
    _entitiesToKill.clear();
    _deltaTime = _clock.getElapsedTime().asSeconds();
    _clock.restart();
    _mouse.update();
    _systemManager->update(_deltaTime);

    receivePacket();

    if (_entitiesToKill.empty())
        return;
    std::vector<Entity> entities = _systemManager->getSystem<ChildSystem>()->_entities;
    for (auto &entity : _entitiesToKill)
        for (auto &child : entities)
            if (getComponent<Child>(child)._parent == entity)
                killEntity(child);
    for (auto &entity : _entitiesToKill)
        destroyEntity(entity);
}

Entity Coordinator::createEntity()
{
    return _entityManager->createEntity();
}

void Coordinator::destroyEntity(Entity entity)
{
    _entityManager->destroyEntity(entity);
    _systemManager->entityDestroyed(entity);
    _componentManager->entityDestroyed(entity);
}

void Coordinator::killEntity(Entity entity)
{
    _entitiesToKill.push_back(entity);
}

sf::Texture* Coordinator::getTexture(textureType type)
{
    for (auto &texture : _textures)
        if (texture.first == type)
            return &texture.second;
    return nullptr;
}

Entity Coordinator::getEntityFromTag(std::string tag)
{
    std::vector<Entity> entities = getAllEntitiesWithComponent<Tag>();
    for (auto &e : entities) {
        auto &t = getComponent<Tag>(e);
        if (t._tag == tag)
            return e;
    }
    std::cerr << "Error: No entity with tag " << tag << std::endl;
    return NULL_ENTITY;
}

std::vector<Entity> Coordinator::getEntitiesFromTag(std::string tag)
{
    std::vector<Entity> finalEntities;

    std::vector<Entity> entities = getAllEntitiesWithComponent<Tag>();
    for (auto &e : entities) {
        auto &t = getComponent<Tag>(e);
        if (t._tag == tag)
            finalEntities.push_back(e);
    }
    return finalEntities;
}

void Coordinator::removeEntitiesFromTag(std::string tag)
{
    std::vector<Entity> entities = getEntitiesFromTag(tag);
    for (auto &e : entities)
        killEntity(e);
}

void Coordinator::sendPacket(std::vector<unsigned char> data, int id)
{
    _networkManager->sendPacket(data, id);
}

void Coordinator::receivePacket()
{
    _networkManager->receivePacket();
}

std::vector<unsigned char> Coordinator::makePacket(unsigned char command, const std::vector<unsigned char>& data)
{
    return _networkManager->makePacket(command, data);
}
