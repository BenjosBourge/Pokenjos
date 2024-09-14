/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray()
{
    const char* typeName = typeid(T).name();

    for (auto const& pair : _componentsArray)
        if (pair.first == typeName)
            return std::static_pointer_cast<ComponentArray<T>>(pair.second);
    return nullptr;
}

template <typename T>
void ComponentManager::addComponent(Entity entity)
{
    if (getComponentArray<T>() == nullptr) {
        std::cerr << "Component not registered" << std::endl;
        return;
    }
    getComponentArray<T>()->addComponent(entity);
    Signature signature = getComponentSignature<T>();
    Signature entitySignature = _entityManager->getSignature(entity);
    _entityManager->setSignature(entity, entitySignature | signature);
}

template <typename T>
void ComponentManager::addComponent(Entity entity, T componentType) {
    if (getComponentArray<T>() == nullptr) {
        std::cerr << "Component not registered" << std::endl;
        return;
    }
    getComponentArray<T>()->addComponent(entity, componentType);
    Signature signature = getComponentSignature<T>();
    Signature entitySignature = _entityManager->getSignature(entity);
    _entityManager->setSignature(entity, entitySignature | signature);
}

template <typename T>
void ComponentManager::removeComponent(Entity entity)
{
    if (getComponentArray<T>() == nullptr) {
        std::cerr << "Component not registered" << std::endl;
        return;
    }
    getComponentArray<T>()->removeComponent(entity);
    Signature signature = getComponentSignature<T>();
    Signature entitySignature = _entityManager->getSignature(entity);
    _entityManager->setSignature(entity, entitySignature & ~signature);
}

template <typename T>
T& ComponentManager::getComponent(Entity entity)
{
    if (getComponentArray<T>() == nullptr) {
        std::cerr << "Component not registered, returning a temporary component" << std::endl;
        return *std::make_shared<T>();
    }
    return getComponentArray<T>()->getComponent(entity);
}

template <typename T>
void ComponentManager::registerComponent()
{
    const char* typeName = typeid(T).name();

    _componentsArray.push_back(std::make_pair(typeName, std::make_shared<ComponentArray<T>>()));
}

template <typename T>
Signature ComponentManager::getComponentSignature()
{
    Signature signature;

    for (int i = 0; i < _componentsArray.size(); i++)
        if (_componentsArray[i].first == typeid(T).name())
            signature.set(i, true);
    return signature;
}

template <typename T>
std::vector<Entity> ComponentManager::getAllEntitiesWithComponent()
{
    std::vector<Entity> entities;

    for (auto const& pair : _componentsArray)
        if (pair.first == typeid(T).name())
            return pair.second->getListOfEntities();
    return entities;
}