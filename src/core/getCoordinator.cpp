/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/coordinator.hpp"

std::shared_ptr<Coordinator> getCoordinator()
{
    static std::shared_ptr<Coordinator> coordinator = nullptr;
    if (coordinator == nullptr) {
        coordinator = std::make_shared<Coordinator>();
        coordinator->init();
    }
    return coordinator;
}