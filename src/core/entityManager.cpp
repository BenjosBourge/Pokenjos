/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include "../../include/core/entityManager.hpp"

EntityManager::EntityManager()
{
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
        _freeEntities.push(entity);
}

EntityManager::~EntityManager()
{

}

Entity EntityManager::createEntity()
{
    if (_freeEntities.empty()) {
        std::cerr << "ERROR: No more entities available." << std::endl;
        return -1;
    }
    Entity entity = _freeEntities.front();
    _freeEntities.pop();
    _existingEntities.emplace_back(entity, 0);
    return entity;
}

void EntityManager::destroyEntity(Entity entity)
{
    std::vector<std::pair<Entity, Signature>> newExistingEntities;
    for (auto &existingEntity : _existingEntities)
        if (existingEntity.first != entity)
            newExistingEntities.push_back(existingEntity);
    _existingEntities = newExistingEntities;
    _freeEntities.push(entity);
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
    for (auto &existingEntity : _existingEntities)
        if (existingEntity.first == entity)
            existingEntity.second = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
    for (auto &existingEntity : _existingEntities)
        if (existingEntity.first == entity)
            return existingEntity.second;
    return 0;
}
