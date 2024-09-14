/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/ecs.hpp"
#include "../../include/core/networkManager.hpp"

NetworkManager::NetworkManager()
{
    _isConnected = false;
    _id = -1;
    _isGameRunning = false;
    _clock.restart();
}

NetworkManager::~NetworkManager()
{
    _socket.disconnect();
}

std::vector<unsigned char> NetworkManager::makePacket(unsigned char command, const std::vector<unsigned char>& data)
{
    std::vector<unsigned char> packet;
    packet.push_back(0xeb);
    packet.push_back(0xb0);
    packet.push_back(data.size() + 4);
    packet.push_back(command);
    for (unsigned char i : data)
        packet.push_back(i);
    return packet;
}