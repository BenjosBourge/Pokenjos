/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <SFML/Network.hpp>

class Client
{
public:
    Client() {

    }

    sf::TcpSocket _socket;
    sf::IpAddress _ip;
    unsigned short _port;
    bool _isConnected;
    std::string _name;
    bool _isReady;
};

#define MAX_CLIENTS 4

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    static std::vector<unsigned char> makePacket(unsigned char command, const std::vector<unsigned char>& data);

    void connect(const std::string& ip, int port);
    void sendPacket(std::vector<unsigned char> data, int id = 0);
    void receivePacket();
    static void parsePacket(std::vector<unsigned char> data, int id = 0);

    int _id;
    sf::TcpSocket _socket;
    bool _isConnected;
    sf::SocketSelector _selector;
    sf::TcpListener _listener;

    bool _isGameRunning;

    Client _clients[MAX_CLIENTS];
    Client _myClient;

    sf::Clock _clock;
};
