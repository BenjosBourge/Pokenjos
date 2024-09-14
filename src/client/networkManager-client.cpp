/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/ecs.hpp"
#include "../../include/core/networkManager.hpp"
#include "../../include/core/coordinator.hpp"
#include "../../include/core/components/text.hpp"
#include "../../include/core/components/spriteRenderer.hpp"
#include "../../include/core/components/transform.hpp"

void NetworkManager::sendPacket(std::vector<unsigned char> data, int id)
{
    if (!_isConnected) {
        //std::cerr << "Error: Not connected" << std::endl;
        return;
    }

    std::cout << id << std::endl;
    if (_socket.send(data.data(), data.size()) != sf::Socket::Done) {
        std::cerr << "Error sending data" << std::endl;
        return;
    } else
        std::cout << "Packet sent" << std::endl;
}

void NetworkManager::connect(const std::string& ip, int port)
{
    sf::Socket::Status status = _socket.connect(ip, port);
    if (status != sf::Socket::Done) {
        std::cout << "Cannot connect to the server" << std::endl;
        return;
    } else if (!_isConnected) {
        std::shared_ptr<Coordinator> coordinator = getCoordinator();
        coordinator->_networkManager->_isConnected = true;
        _selector.add(_socket);

        Entity entity = coordinator->getEntityFromTag("buttonNameText");
        std::string name = coordinator->getComponent<Text>(entity)._text;
        std::vector<unsigned char> nameBytes;
        for (char i : name)
            nameBytes.push_back(i);

        //send packet
    }
    std::cout << "Connected to the server" << std::endl;
}

void NetworkManager::receivePacket() {
    if (!_isConnected) {
        //std::cerr << "Error: Not connected" << std::endl;
        return;
    }

    if (_selector.wait(sf::milliseconds(1))) {
        if (_selector.isReady(_socket)) {
            sf::Packet packet;
            std::vector<char> receivedData(100);
            std::size_t receivedSize = 0;
            sf::Socket::Status status;

            std::cout << "Packet get" << std::endl;
            do {
                //receivedData.resize(receivedSize + 100);
                status = _socket.receive(receivedData.data() + receivedSize, receivedData.size() - receivedSize, receivedSize);
            } while (status == sf::Socket::Partial);

            if (status == sf::Socket::Done) {
                std::cout << "Received " << receivedSize << " bytes" << std::endl;
                std::vector<unsigned char> data(receivedData.begin(), receivedData.end());
                parsePacket(data);
            } else if (status == sf::Socket::Disconnected) {
                std::cout << "Server Disconnected" << std::endl;
                _isConnected = false;
            }
        }
    }
}


void functionPing(const std::vector<unsigned char>& data)
{
    //change all
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    int ping_time = coordinator->_networkManager->_clock.getElapsedTime().asMilliseconds();
    std::cout << std::dec << "Ping: " << ping_time << "ms" << std::endl;
}


const std::vector<std::pair<unsigned char, void (*)(const std::vector<unsigned char>&)>> packetFunctions = {
    {0x00, &functionPing},
};

/*
 * Packet structure
 * 0xeb 0xb0 size command data
 *
 * Network Protocole
 * Header: 2 bytes
 * Size : 1 bytes
 * Command : 1 bytes
 *
 * Header: 0xeb 0xb0 by default
 */

void NetworkManager::parsePacket(std::vector<unsigned char> data, int id)
{
    std::cout << "Parsing packet" << std::endl;
    while (data.size() > 3 && data[0] == 0xeb && data[1] == 0xb0) {
        int size = data[2] - 4;

        std::cout << "Packet size: " << size << std::endl;
        std::vector<unsigned char> data2;
        data2.reserve(size);
        for (int i = 0; i < size; i++) {
            data2.push_back(data[i + 4]);
            std::cout << std::hex << (int) data[i + 4] << " ";
        }
        std::cout << std::endl;

        for (auto &i: packetFunctions)
            if (i.first == data[3]) {
                i.second(data2);
                break;
            }

        for (int i = 0; i < size + 4; i++)
            data.erase(data.begin());
        std::cout << "Data size: " << data.size() << std::endl;
    }
}
