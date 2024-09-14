/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <utility>

#include "../../../include/core/components/text.hpp"

Text::Text()
{
    _text = "";
    _fontSize = 10;
    _color = sf::Color::White;
}

Text::Text(std::string text, int fontSize) : Text()
{
    _text = std::move(text);
    _fontSize = fontSize;
}

Text::Text(std::string text, int fontSize, sf::Color color) : Text()
{
    _text = std::move(text);
    _fontSize = fontSize;
    _color = color;
}

Text::~Text()
{

}