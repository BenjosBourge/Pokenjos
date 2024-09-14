/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/coordinator.hpp"

void Coordinator::loadTextures()
{
    _font.loadFromFile("assets/neon_pixel-7.ttf");

    sf::Texture texture;
    texture.loadFromFile("assets/blank_square.png");
    _textures.emplace_back(TEXTURE_TYPE_EXAMPLE, texture);
}