/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/cameraSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/ecs.hpp"
#include "../../../../include/core/components/camera.hpp"

CameraSystem::CameraSystem()
{
    _signature = getCoordinator()->getComponentSignature<Camera>();
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (int i = 0; i < _entitiesThisFrame.size(); i++) {
        auto &camera = coordinator->getComponent<Camera>(_entitiesThisFrame[i]);

        if (camera._isShadingProgressive) {
            if (camera._cameraColor.r == camera._shadingColor.r &&
                camera._cameraColor.g == camera._shadingColor.g &&
                camera._cameraColor.b == camera._shadingColor.b)
                continue;
            int r = (camera._shadingColor.r - camera._cameraColor.r) * deltaTime * 10.f;
            int g = (camera._shadingColor.g - camera._cameraColor.g) * deltaTime * 10.f;
            int b = (camera._shadingColor.b - camera._cameraColor.b) * deltaTime * 10.f;

            camera._cameraColor.r += r;
            camera._cameraColor.g += g;
            camera._cameraColor.b += b;
        } else
            camera._cameraColor = camera._shadingColor;
    }
}

void CameraSystem::addedEntity(Entity entity)
{

}

void CameraSystem::removedEntity(Entity entity)
{

}