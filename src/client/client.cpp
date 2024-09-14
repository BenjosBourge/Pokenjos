/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/coordinator.hpp"

void Coordinator::initWindow()
{
    _window = new sf::RenderWindow(sf::VideoMode(800, 600), "ECS");//, sf::Style::Fullscreen);
    _window->setFramerateLimit(240);
}

bool isServer()
{
    return false;
}

int serverRunning()
{
    return 0;
}