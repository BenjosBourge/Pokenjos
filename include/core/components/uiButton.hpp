/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../entity.hpp"
#include "transform.hpp"

class UiButton {
public:
    UiButton();
    UiButton(void (*function)(Entity));
    UiButton(void (*function)(Entity), float delay);
    ~UiButton();

    Entity _text;

    //Clicking
    void (*_functionClicked)(Entity);
    void (*_functionUnclicked)(Entity);
    bool _firstFrameClicked;
    bool _isClicked;
    bool _isActivated;
    void (*_functionFirstTimeClicked)(Entity);
    bool _neverClicked;

    //Hovering
    void setZoomWhenHovered(bool flag, const Transform& transform);
    sf::Vector2f _scale;
    bool _zoomWhenHovered;
    bool _isHovered;
    float _currentSize;

    //Activated
    void setFunctionActivated(void (*function)(Entity));
    bool _canBeActivated;
    bool _writableWhenActivated;
    void (*_functionWhenActivated)(Entity);
    sf::Color _colorWhenActivated;

    float _delay;
    float _timer; //timer is always going back to 0
    float _timerKeys[36]{};
};
