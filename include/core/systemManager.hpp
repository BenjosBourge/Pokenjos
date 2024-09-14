/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "entity.hpp"
#include "entityManager.hpp"
#include "componentManager.hpp"
#include "system.hpp"

class SystemManager {
public:
    SystemManager();
    ~SystemManager();

    void init();
    template<typename T> void registerSystem();
    template<typename T> void setSignature(Signature signature);
    void entityDestroyed(Entity entity);
    void entitySignatureChanged(Entity entity, Signature entitySignature);

    template<typename T> std::shared_ptr<T> getSystem();

    void update(float deltaTime);

    std::vector<std::pair<const char*, std::shared_ptr<System>>> _systems;

    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<ComponentManager> _componentManager;
};

#include "../../src/core/systemManager.tpp"
