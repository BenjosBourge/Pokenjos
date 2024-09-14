/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include "../../include/core/componentManager.hpp"
#include "../../include/core/myComponents.hpp"

ComponentManager::ComponentManager()
{

}

ComponentManager::~ComponentManager()
{

}

void ComponentManager::init()
{
    registerComponent<Transform>();
    registerComponent<SpriteRenderer>();
    registerComponent<Animator>();
    registerComponent<LifeTimer>();
    registerComponent<Trail>();
    registerComponent<BoxCollider>();
    registerComponent<Tag>();
    registerComponent<Camera>();
    registerComponent<UserInterface>();
    registerComponent<InteractionBoxCollider>();
    registerComponent<UiButton>();
    registerComponent<Child>();
    registerComponent<Text>();
    registerComponent<PlayerController>();
}

void ComponentManager::entityDestroyed(Entity entity)
{
    for (auto const& component : _componentsArray) {
        component.second->entityDestroyed(entity);
    }
}
