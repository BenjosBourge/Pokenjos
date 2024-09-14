/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>

template<typename T>
void SystemManager::registerSystem()
{
    std::shared_ptr<T> system = std::make_shared<T>();
    _systems.push_back(std::make_pair(typeid(T).name(), system));
}

template<typename T>
void SystemManager::setSignature(Signature signature)
{
    auto system = getSystem<T>();
    system->_signature = signature;
}

template<typename T>
std::shared_ptr<T> SystemManager::getSystem()
{
    for (auto const& system : _systems) {
        if (system.first == typeid(T).name())
            return std::static_pointer_cast<T>(system.second);
    }
    return nullptr;
}
