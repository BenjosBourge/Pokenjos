/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class Text {
public:
    Text();
    Text(std::string text, int fontSize);
    Text(std::string text, int fontSize, sf::Color color);
    ~Text();

    std::string _text;
    sf::Color _color;
    int _fontSize;
};
