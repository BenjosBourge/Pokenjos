/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>

template<typename T>
ComponentArray<T>::ComponentArray()
{

}

template<typename T>
ComponentArray<T>::~ComponentArray()
{

}

template<typename T>
void ComponentArray<T>::addComponent(Entity entity)
{
    if (entity == NULL_ENTITY) {
        std::cerr << "Cannot add a component to a null entity" << std::endl;
        return;
    }
    for (auto& tcomponent : _components)
        if (tcomponent.first == entity) {
            std::cout << "Component already exists" << std::endl;
            return;
        }

    _components.push_back(std::make_pair(entity, std::make_shared<T>()));
}

template<typename T>
void ComponentArray<T>::addComponent(Entity entity, T component)
{
    if (entity == NULL_ENTITY) {
        std::cerr << "Cannot add a component to a null entity" << std::endl;
        return;
    }
    for (auto& tcomponent : _components)
        if (tcomponent.first == entity) {
            std::cerr << "Component already exists" << std::endl;
            return;
        }

    _components.push_back(std::make_pair(entity, std::make_shared<T>(component)));
}

template<typename T>
void ComponentArray<T>::removeComponent(Entity entity)
{
    if (entity == NULL_ENTITY) {
        std::cerr << "Cannot remove a component of a null entity" << std::endl;
        return;
    }
    std::vector<std::pair<Entity, std::shared_ptr<T>>> newComponents;
    for (auto& tcomponent : _components)
        if (tcomponent.first != entity)
            newComponents.push_back(tcomponent);
    _components = newComponents;
}

template<typename T>
T& ComponentArray<T>::getComponent(Entity entity)
{
    if (entity == NULL_ENTITY) {
        std::cerr << "Cannot get a component of a null entity" << std::endl;
        return *std::make_shared<T>();
    }
    for (auto& tcomponent : _components)
        if (tcomponent.first == entity)
            return *tcomponent.second;
    std::cerr << "Component not found: " << typeid(T).name() << " in entity " << entity << std::endl;
    return *std::make_shared<T>();
}

template<typename T>
void ComponentArray<T>::entityDestroyed(Entity entity)
{
    if (entity == NULL_ENTITY) {
        std::cerr << "Cannot destroy a null entity" << std::endl;
        return;
    }
    std::vector<std::pair<Entity, std::shared_ptr<T>>> newComponents;
    for (auto& tcomponent : _components)
        if (tcomponent.first != entity)
            newComponents.push_back(tcomponent);
    _components = newComponents;
}

template<typename T>
std::vector<Entity> ComponentArray<T>::getListOfEntities()
{
    std::vector<Entity> newEntities;

    for (auto& tcomponent : _components)
        newEntities.push_back(tcomponent.first);
    return newEntities;
}