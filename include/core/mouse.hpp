/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once

class Mouse {
public:
    Mouse();
    ~Mouse();

    void update();
    sf::Vector2i getMousePosition() const { return {_x, _y}; }

    bool _leftButtonPressed;
    bool _leftButtonHold;
    bool _leftButtonReleased;
    bool _rightButtonPressed;
    bool _rightButtonHold;
    bool _rightButtonReleased;

    int _x;
    int _y;
};
