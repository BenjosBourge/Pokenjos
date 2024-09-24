/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <SFML/Graphics.hpp>
#include "../../../include/core/components/uiButton.hpp"
#include "../../../include/core/components/transform.hpp"

UiButton::UiButton()
{
    _scale = sf::Vector2f(1, 1);
    _zoomWhenHovered = false;
    _isHovered = false;
    _currentSize = 1;
    _zoomEffect = 1.05;
    _zoomSpeed = 1;
    _dezoomSpeed = 1;
    _delay = 0;
    _isActivated = false;
    _firstFrameClicked = false;
    _canBeActivated = false;
    _isClicked = false;
    _functionWhenActivated = nullptr;
    _functionClicked = nullptr;
    _functionUnclicked = nullptr;
    _colorWhenActivated = sf::Color(255, 255, 255);
    _neverClicked = true;
    _functionFirstTimeClicked = nullptr;
    _writableWhenActivated = false;
    _timer = 0;
    for (int i = 0; i < 36; i += 1)
        _timerKeys[i] = 0;
    _text = NULL_ENTITY;
    _id = 0;
}

UiButton::UiButton(void (*function)(Entity)) : UiButton()
{
    _functionClicked = function;
    _currentSize = 1;
    _isHovered = false;
}

UiButton::UiButton(void (*function)(Entity), float delay) : UiButton()
{
    _functionClicked = function;
    _currentSize = 1;
    _isHovered = false;
    _delay = delay;
}

void UiButton::setZoomWhenHovered(bool flag, const Transform& transform)
{
    _zoomWhenHovered = flag;
    _scale = sf::Vector2f(transform._width, transform._height);
}

void UiButton::setFunctionActivated(void (*function)(Entity))
{
    _functionWhenActivated = function;
    _canBeActivated = true;
    _colorWhenActivated = sf::Color(255, 255, 60);
}

UiButton::~UiButton()
{

}
