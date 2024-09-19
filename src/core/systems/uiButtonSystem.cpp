/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/uiButtonSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/components/interactionBoxCollider.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/components/uiButton.hpp"
#include "../../../../include/core/components/ui.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"
#include "../../../../include/core/components/text.hpp"
#include "../../../../include/core/ecs.hpp"

UiButtonSystem::UiButtonSystem()
{
    _signature = getCoordinator()->getComponentSignature<UiButton>();
    _signature |= getCoordinator()->getComponentSignature<UserInterface>();
    _signature |= getCoordinator()->getComponentSignature<InteractionBoxCollider>();
    _signature |= getCoordinator()->getComponentSignature<Transform>();
}

UiButtonSystem::~UiButtonSystem()
{

}

void UiButtonSystem::update(float deltaTime)
{
    if (isServer())
        return;
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    if (!coordinator->_window->hasFocus())
        return;
    sf::Vector2i mousePos = sf::Mouse::getPosition(*coordinator->_window);

    for (auto const& entity : _entitiesThisFrame) {
        auto &uiButton = coordinator->getComponent<UiButton>(entity);
        auto &interactionBoxCollider = coordinator->getComponent<InteractionBoxCollider>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

        if (uiButton._delay > 0) {
            uiButton._delay -= deltaTime;
            continue;
        }
        if (uiButton._timer > 0)
            uiButton._timer -= deltaTime;
        for (int i = 0; i < 36; i += 1) {
            if (uiButton._timerKeys[i] > 0)
                uiButton._timerKeys[i] -= deltaTime;
        }
        uiButton._firstFrameClicked = false;

        if (uiButton._functionClicked != nullptr) {
            Entity camera = coordinator->getEntityFromTag("camera");
            auto &cameraTransform = coordinator->getComponent<Transform>(camera);

            int x = transform._x - cameraTransform._x + 1920 / 2;
            int y = transform._y - cameraTransform._y + 1080 / 2;

            if (mousePos.x >= x - interactionBoxCollider._width / 2
                && mousePos.x <= x + interactionBoxCollider._width / 2
                && mousePos.y >= y - interactionBoxCollider._height / 2
                && mousePos.y <= y + interactionBoxCollider._height / 2) {
                uiButton._isHovered = true;

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (!uiButton._isClicked)
                        uiButton._firstFrameClicked = true;
                    uiButton._isClicked = true;
                    if (uiButton._neverClicked) {
                        uiButton._neverClicked = false;
                        if (uiButton._functionFirstTimeClicked != nullptr)
                            uiButton._functionFirstTimeClicked(entity);
                    }

                    if (uiButton._firstFrameClicked) {
                        if (uiButton._isActivated && uiButton._functionUnclicked != nullptr)
                            uiButton._functionUnclicked(entity);
                        else
                            uiButton._functionClicked(entity);
                        uiButton._isActivated = !uiButton._isActivated;

                        if (uiButton._canBeActivated) {
                            if (uiButton._isActivated) {
                                if (coordinator->hasComponent<SpriteRenderer>(entity))
                                    coordinator->getComponent<SpriteRenderer>(
                                            entity)._color = uiButton._colorWhenActivated;
                            } else {
                                if (coordinator->hasComponent<SpriteRenderer>(entity))
                                    coordinator->getComponent<SpriteRenderer>(entity)._color = sf::Color(255, 255, 255);
                            }
                        }
                    }
                } else
                    uiButton._isClicked = false;
            } else
                uiButton._isHovered = false;
        }

        if (uiButton._zoomWhenHovered) {
            if (uiButton._isHovered) {
                float delta = deltaTime * 1 * ((uiButton._scale.x * (1.05f)) - transform._width);

                uiButton._currentSize += delta;
            } else {
                float delta = deltaTime * 1 * (uiButton._scale.x - transform._width);

                uiButton._currentSize += delta;
            }
            transform._width = uiButton._scale.x * uiButton._currentSize;
            transform._height = uiButton._scale.y * uiButton._currentSize;
        }

        if (uiButton._canBeActivated) {
            if (uiButton._isActivated && uiButton._functionWhenActivated != nullptr)
                uiButton._functionWhenActivated(entity);

            if (uiButton._isActivated && uiButton._writableWhenActivated && uiButton._text != NULL_ENTITY) {
                auto &text = coordinator->getComponent<Text>(uiButton._text);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !text._text.empty()) {
                    if (uiButton._timer <= 0) {
                        uiButton._timer = 0.1f;
                        text._text.pop_back();
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    uiButton._timer = 0.5f;
                    uiButton._isActivated = false;
                    if (uiButton._functionUnclicked != nullptr)
                        uiButton._functionUnclicked(entity);
                    if (coordinator->hasComponent<SpriteRenderer>(entity))
                        coordinator->getComponent<SpriteRenderer>(entity)._color = sf::Color(255, 255, 255);
                } else {
                    for (int i = 0; i < 26; i++) {
                        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(i))) {
                            if ( uiButton._timerKeys[i] <= 0) {
                                text._text += (char) (i + 65);
                                uiButton._timerKeys[i] = 0.2f;
                            }
                        } else
                            uiButton._timerKeys[i] = 0.f;
                    }
                    for (int i = 0; i < 10; i++) {
                        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(i + 26))) {
                            if (uiButton._timerKeys[i] <= 0) {
                                text._text += (char) (i + 48);
                                uiButton._timerKeys[i] = 0.2f;
                            }
                            else
                                uiButton._timerKeys[i] = 0.f;
                        }
                    }
                }
            }
        }
    }
}

void UiButtonSystem::addedEntity(Entity entity)
{

}

void UiButtonSystem::removedEntity(Entity entity)
{

}