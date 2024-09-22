/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <cmath>
#include "../../include/core/ecs.hpp"
#include "../../include/core/myMath.hpp"

float getNorm(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float getNorm(sf::Vector2f vector, sf::Vector2f target)
{
    return std::sqrt((target.x - vector.x) * (target.x - vector.x) + (target.y - vector.y) * (target.y - vector.y));
}

sf::Vector2f getNormalizedVector(sf::Vector2f vector)
{
    float length = getNorm(vector);

    if (length != 0)
        return sf::Vector2f(vector.x / length, vector.y / length);
    return vector;
}

sf::Vector2f getNormalizedVector(sf::Vector2f vector, sf::Vector2f target)
{
    float length = getNorm(sf::Vector2f(target.x - vector.x, target.y - vector.y));

    if (length != 0)
        return sf::Vector2f((target.x - vector.x) / length, (target.y - vector.y) / length);
    return vector;
}

sf::Vector2f getDirection(Direction direction)
{
    switch (direction)
    {
        case Direction::UP:
            return {0, -1};
        case Direction::DOWN:
            return {0, 1};
        case Direction::LEFT:
            return {-1, 0};
        case Direction::RIGHT:
            return {1, 0};
    }
    return {0, 0};
}

sf::Vector2f getPositionOfTile(int x, int y)
{
    return {static_cast<float>(72 * x + 1920/2 - 72 * 12 + 36), static_cast<float>(72 * y + 1080/2 - 72 * 6 + 36 + 40)};
}

float my_step(float a, float b) {
    return a < b ? 0.0 : 1.0;
}

float my_sin(float x) {
    return sin(x);
}

float my_cos(float x) {
    return cos(x);
}
