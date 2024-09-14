/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/textRenderingSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/components/text.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/ecs.hpp"

TextRenderingSystem::TextRenderingSystem()
{
    _signature = getCoordinator()->getComponentSignature<Text>();
    _signature |= getCoordinator()->getComponentSignature<Transform>();
}

TextRenderingSystem::~TextRenderingSystem()
{

}

void TextRenderingSystem::update(float deltaTime)
{
    if (isServer())
        return;
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const& entity : _entitiesThisFrame) {
        auto &text = coordinator->getComponent<Text>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

        sf::Text sfText;
        sfText.setFont(coordinator->_font);
        sfText.setString(text._text);
        sfText.setCharacterSize(text._fontSize);
        sfText.setFillColor(text._color);
        sfText.setPosition(transform._x, transform._y);
        coordinator->_window->draw(sfText);
    }
}

void TextRenderingSystem::addedEntity(Entity entity)
{

}

void TextRenderingSystem::removedEntity(Entity entity)
{

}