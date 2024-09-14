/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/ecs.hpp"
#include "../../include/core/networkManager.hpp"
#include "../../include/core/coordinator.hpp"
#include "../../include/core/components/transform.hpp"

void canLaunchAGame();
void allCharacterReady();

void NetworkManager::sendPacket(std::vector<unsigned char> data, int id)
{
    if (!_isConnected) {
        std::cerr << "Error: Not connected" << std::endl;
        return;
    }

    std::cout << "Sending packet:" << std::endl;
    for (int i = 0; i < data.size(); i++)
        std::cout << std::hex << (int)data[i] << " ";
    std::cout << std::endl;

    std::cout << id << std::endl;
    if (!_clients[id]._isConnected) {
        std::cerr << "Error:Client " << id << " Not connected" << std::endl;
        return;
    }
    if (_clients[id]._socket.send(data.data(), data.size()) != sf::Socket::Done) {
        std::cerr << "Error sending data" << std::endl;
        return;
    } else
        std::cout << "Packet sent" << std::endl;
}

void NetworkManager::connect(const std::string& ip, int port)
{
    _isConnected = true;
    _listener.listen(53000);
    _selector.add(_listener);
}

void NetworkManager::receivePacket()
{
    if (_selector.wait(sf::milliseconds(10))) {
        if (_selector.isReady(_listener)) {
            std::size_t n = MAX_CLIENTS;
            for (std::size_t i = 0; i < MAX_CLIENTS; ++i) {
                if (!_clients[i]._isConnected) {
                    n = i;
                    break;
                }
            }
            if (n == MAX_CLIENTS)
                std::cerr << "Too many clients" << std::endl;
            else if (_listener.accept(_clients[n]._socket) == sf::Socket::Done) {
                std::cout << "Client connected : " << _clients[n]._socket.getRemoteAddress() << std::endl;
                _clients[n]._ip = _clients[n]._socket.getRemoteAddress();
                _clients[n]._port = _clients[n]._socket.getRemotePort();
                _clients[n]._isConnected = true;
                _selector.add(_clients[n]._socket);

                //send a packet for confirmation
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++)
            std::cout << _clients[i]._isConnected << " ";
        std::cout << std::endl;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (_clients[i]._isConnected && _selector.isReady(_clients[i]._socket)) {
                std::vector<char> receivedData(100);
                std::size_t receivedSize = 0;
                sf::Socket::Status status;

                do {
                    status = _clients[i]._socket.receive(receivedData.data() + receivedSize, receivedData.size() - receivedSize, receivedSize);
                } while (status == sf::Socket::Partial);

                if (status == sf::Socket::Done) {
                    std::cout << "Received " << receivedSize << " bytes from " << _clients[i]._ip << std::endl;
                    std::vector<unsigned char> data(receivedData.begin(), receivedData.end());
                    parsePacket(data, i);
                } else if (status == sf::Socket::Disconnected) {
                    std::cout << "Client Disconnected : " << _clients[i]._ip << std::endl;
                    _clients[i]._isConnected = false;
                    _selector.remove(_clients[i]._socket);
                }
            }
        }
    }
}


void functionPing(const std::vector<unsigned char>& data, int id)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    coordinator->sendPacket(coordinator->makePacket(0x00, {}), id);
}


const std::vector<std::pair<unsigned char, void (*)(const std::vector<unsigned char>&, int id)>> packetFunctions = {
        {0x00,&functionPing},
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

        std::cout << "Size: " << size << std::endl;
        std::vector<unsigned char> data2;
        data2.reserve(size);
        for (int i = 0; i < size; i++)
            data2.push_back(data[i + 4]);

        for (auto &i: data)
            std::cout << std::hex << (int) i << " ";
        std::cout << std::endl << "------" << std::endl;

        for (auto &i: data2)
            std::cout << std::hex << (int) i << " ";
        std::cout << std::endl;

        for (auto &i: packetFunctions)
            if (i.first == data[3]) {
                i.second(data2, id);
                break;
            }

        for (int i = 0; i < size + 4; i++)
            data.erase(data.begin());
    }
}
