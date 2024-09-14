/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <ctime>
#include "../../include/core/ecs.hpp"
#include "../../include/core/systemManager.hpp"
#include "../../include/core/mySystems.hpp"
#include "../../include/core/coordinator.hpp"

SystemManager::SystemManager()
{

}

SystemManager::~SystemManager()
{

}

void SystemManager::init()
{
    registerSystem<DrawSystem>();
    registerSystem<AnimationSystem>();

    /*Collision after movement*/
    registerSystem<CollisionSystem>();
    registerSystem<InteractionCollisionSystem>();

    registerSystem<LifeTimerSystem>();
    registerSystem<TrailSystem>();
    registerSystem<CameraSystem>();
    registerSystem<UiButtonSystem>();
    registerSystem<ChildSystem>();
    registerSystem<TextRenderingSystem>();
    registerSystem<PlayerMovementSystem>();
}

void SystemManager::entityDestroyed(Entity entity)
{
    for (auto const& system : _systems) {
        bool found = false;
        std::vector<Entity> entities;
        for (auto &tentity : system.second->_entities) {
            if (tentity != entity)
                entities.push_back(tentity);
            else
                found = true;
        }
        system.second->_entities = entities;
        if (found)
            system.second->removedEntity(entity);
    }
}

void SystemManager::entitySignatureChanged(Entity entity, Signature entitySignature)
{
    for (auto const& system : _systems) {
        auto const& type = system.second->_signature & entitySignature;
        if (type == system.second->_signature) {
            bool found = false;
            for (auto &tentity : system.second->_entities)
                if (tentity == entity)
                    found = true;
            if (!found) {
                system.second->_entities.push_back(entity);
                system.second->addedEntity(entity);
            }
        } else {
            std::vector<Entity> entities;
            bool found = false;
            for (auto &tentity : system.second->_entities) {
                if (tentity != entity)
                    entities.push_back(tentity);
                else
                    found = true;
            }
            system.second->_entities = entities;
            if (found)
                system.second->removedEntity(entity);
        }
    }
}

void SystemManager::update(float deltaTime)
{
    float biggest = 0;
    std::string name;
    clock_t start;
    clock_t end;

    if (!isDebug()) {
        for (auto& system : _systems)
            system.second->update(deltaTime);
        return;
    }

    for (auto& system : _systems)
        system.second->_entitiesThisFrame = system.second->_entities;

    for (auto& system : _systems) {
        start = clock();
        system.second->update(deltaTime);
        end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        if (elapsed > biggest) {
            biggest = (float) elapsed;
            name = typeid(*system.second).name();
        }
    }

    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    coordinator->_highConsumingSystem = name;
    coordinator->_highConsumingTime = biggest;
}
