/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/camera.hpp"

Camera::Camera()
{
    _backgroundColor = sf::Color::Black;
    _cameraColor = sf::Color::White;
    _isShadingProgressive = true;
    _shadingColor = _cameraColor;
}

Camera::~Camera()
{

}
