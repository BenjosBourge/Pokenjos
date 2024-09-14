/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/spriteRenderer.hpp"

SpriteRenderer::SpriteRenderer()
{
    _texture = TEXTURE_TYPE_NONE;
    _offsetX = 0;
    _offsetY = 0;
    _rectWidth = 0;
    _rectHeight = 0;
    _isFlippedHorizontally = false;
    _isFlippedVertically = false;
    _layer = 0;
    _opacity = 1.0f;
    _rotation = 0.0f;
    _overlay = false;
    _color = sf::Color(255, 255, 255);
}

SpriteRenderer::SpriteRenderer(textureType texture, int rectWidth, int rectHeight) : SpriteRenderer()
{
    _texture = texture;
    _rectWidth = rectWidth;
    _rectHeight = rectHeight;
}

SpriteRenderer::SpriteRenderer(textureType texture, int rectWidth, int rectHeight, int layer) : SpriteRenderer()
{
    _texture = texture;
    _rectWidth = rectWidth;
    _rectHeight = rectHeight;
    _layer = layer;
}

SpriteRenderer::SpriteRenderer(textureType texture, int offsetX, int offsetY, int rectWidth, int rectHeight) : SpriteRenderer()
{
    _texture = texture;
    _offsetX = offsetX;
    _offsetY = offsetY;
    _rectWidth = rectWidth;
    _rectHeight = rectHeight;
}

SpriteRenderer::~SpriteRenderer()
{

}