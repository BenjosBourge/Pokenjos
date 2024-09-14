/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/coordinator.hpp"

void Coordinator::initWindow()
{
    //No Window
}

bool isServer()
{
    return true;
}

bool exitFlag = false;

void signalHandler(int signum)
{
    if (signum == SIGINT) {
        std::cout << "Leaving Engine" << std::endl;
        exitFlag = true;
    }
}

int serverRunning()
{
    auto coordinator = getCoordinator();
    std::cout << "Server running" << std::endl;

    signal(SIGINT, signalHandler); //TODO: SIGTERM

    coordinator->_networkManager->connect("", 0000);
    while (!exitFlag)
    {
        coordinator->update();
        coordinator->receivePacket();
    }
    return 1;
}