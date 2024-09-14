/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>

#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    sf::Color _backgroundColor;
    bool _isShadingProgressive; // If true, the camera will be shaded progressively
    sf::Color _cameraColor; //the color used every frame
    sf::Color _shadingColor; // Used for progressive shading
};
