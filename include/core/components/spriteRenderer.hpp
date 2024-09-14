/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include <SFML/Graphics.hpp>
#include "../texture.hpp"

class SpriteRenderer {
public:
    SpriteRenderer();
    SpriteRenderer(textureType texture, int rectWidth, int rectHeight);
    SpriteRenderer(textureType texture, int rectWidth, int rectHeight, int layer);
    SpriteRenderer(textureType texture, int offsetX, int offsetY, int rectWidth, int rectHeight);
    ~SpriteRenderer();

    textureType _texture;
    int _offsetX;
    int _offsetY;
    int _rectWidth;
    int _rectHeight;
    int _layer;
    float _opacity;
    bool _isFlippedHorizontally;
    bool _isFlippedVertically;
    float _rotation;
    sf::Color _color;

    bool _overlay;
};
