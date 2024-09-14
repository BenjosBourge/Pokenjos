/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "entityManager.hpp"
#include "componentManager.hpp"
#include "systemManager.hpp"
#include "texture.hpp"
#include "networkManager.hpp"

class Coordinator
{
public:
    Coordinator();
    ~Coordinator();

    void initWindow();
    sf::RenderWindow* _window;

    void init();
    void update();
    Entity getEntityFromTag(std::string tag);
    std::vector<Entity> getEntitiesFromTag(std::string tag);

    /*Entity Creation and Destruction*/
    Entity createEntity();
    void destroyEntity(Entity entity);
    void killEntity(Entity entity);

    /*Component Management*/
    template<typename T> T &addComponent(Entity entity);
    template<typename T> T &addComponent(Entity entity, T component);
    template<typename T> void removeComponent(Entity entity);
    template<typename T> T& getComponent(Entity entity);
    template<typename T> bool hasComponent(Entity entity);
    template<typename T> Signature getComponentSignature();

    template<typename T> std::vector<Entity> getAllEntitiesWithComponent();

    /*Networking*/
    std::vector<unsigned char> makePacket(unsigned char command, const std::vector<unsigned char>& data);
    void sendPacket(std::vector<unsigned char> data, int id = 0);
    void receivePacket();

    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<ComponentManager> _componentManager;
    std::shared_ptr<SystemManager> _systemManager;
    std::shared_ptr<NetworkManager> _networkManager;

    std::vector<std::pair<textureType, sf::Texture>> _textures;
    sf::Texture* getTexture(textureType type);
    sf::Font _font;
    void loadTextures();

    float _deltaTime;

    /*
     * Debug
     * */
    std::string _highConsumingSystem;
    float _highConsumingTime;
private:
    sf::Clock _clock;
    std::vector<Entity> _entitiesToKill;
};

#include "../../src/core/coordinator.tpp"

std::shared_ptr<Coordinator> getCoordinator();
