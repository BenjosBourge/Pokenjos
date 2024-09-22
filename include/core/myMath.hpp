/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include <SFML/Graphics.hpp>

float getNorm(sf::Vector2f vector);
float getNorm(sf::Vector2f vector, sf::Vector2f target);
sf::Vector2f getNormalizedVector(sf::Vector2f vector);
sf::Vector2f getNormalizedVector(sf::Vector2f vector, sf::Vector2f target);

float my_step(float a, float b);
float my_sin(float x);
float my_cos(float x);
