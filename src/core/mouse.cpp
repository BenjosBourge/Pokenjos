/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <cmath>
#include "../../include/core/ecs.hpp"
#include "../../include/core/coordinator.hpp"

Mouse::Mouse()
{
    _x = 0;
    _y = 0;

    _leftButtonPressed = false;
    _leftButtonHold = false;
    _leftButtonReleased = false;

    _rightButtonPressed = false;
    _rightButtonHold = false;
    _rightButtonReleased = false;
}

Mouse::~Mouse()
{

}

void Mouse::update()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!_leftButtonHold)
            _leftButtonPressed = true;
        _leftButtonHold = true;
    } else {
        if (_leftButtonHold)
            _leftButtonReleased = true;
        _leftButtonHold = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (!_rightButtonHold)
            _rightButtonPressed = true;
        _rightButtonHold = true;
    } else {
        if (_rightButtonHold)
            _rightButtonReleased = true;
        _rightButtonHold = false;
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(*getCoordinator()->_window);
    _x = mousePos.x;
    _y = mousePos.y;
}