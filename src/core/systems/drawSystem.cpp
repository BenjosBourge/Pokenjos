/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../../include/core/systems/drawSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"
#include "../../../../include/core/components/camera.hpp"
#include "../../../../include/core/components/ui.hpp"
#include "../../../../include/core/ecs.hpp"

const std::string vertexShader = R"(
    void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
)";

const std::string fragmentShader = R"(
    uniform sampler2D texture;
    void main() {
        vec4 color = texture2D(texture, gl_TexCoord[0].xy);
        gl_FragColor = vec4(1.0, 1.0, 0.0, color.a); // Jaune avec la même alpha
    }
)";

DrawSystem::DrawSystem()
{
    _signature = getCoordinator()->getComponentSignature<Transform>();
    _signature |= getCoordinator()->getComponentSignature<SpriteRenderer>();
}

DrawSystem::~DrawSystem()
{

}

void DrawSystem::update(float deltaTime)
{
    if (isServer())
        return;
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    float cameraX = 0;
    float cameraY = 0;
    float cameraR = 1;
    float cameraG = 1;
    float cameraB = 1;
    Entity camera = coordinator->getEntityFromTag("camera");
    if (camera != NULL_ENTITY && coordinator->hasComponent<Transform>(camera)
                                && coordinator->hasComponent<Camera>(camera)) {
        auto &transform = coordinator->getComponent<Transform>(camera);
        cameraX = transform._x;
        cameraY = transform._y;

        auto &cameraComponent = coordinator->getComponent<Camera>(camera);
        cameraR = (float)cameraComponent._cameraColor.r / 255.0f;
        cameraG = (float)cameraComponent._cameraColor.g / 255.0f;
        cameraB = (float)cameraComponent._cameraColor.b / 255.0f;
    }
    cameraX -= 1920 / 2;
    cameraY -= 1080 / 2;

    for (auto const& entity : _entitiesThisFrame) {
        sf::Sprite sprite;
        auto &transform = coordinator->getComponent<Transform>(entity);
        auto &spriteRenderer = coordinator->getComponent<SpriteRenderer>(entity);

        int r = spriteRenderer._color.r;
        int g = spriteRenderer._color.g;
        int b = spriteRenderer._color.b;

        sprite.setTexture(*(coordinator->getTexture(spriteRenderer._texture)));
        sprite.setTextureRect({spriteRenderer._offsetX, spriteRenderer._offsetY, spriteRenderer._rectWidth, spriteRenderer._rectHeight});
        sprite.setPosition({transform._x - cameraX, transform._y - cameraY});
        sprite.setRotation(spriteRenderer._rotation);
        sprite.setOrigin({(float)spriteRenderer._rectWidth / 2, (float)spriteRenderer._rectHeight / 2});
        sprite.setScale({transform._width * (spriteRenderer._isFlippedHorizontally ? -1 : 1), transform._height * (spriteRenderer._isFlippedVertically ? -1 : 1)});
        if (!coordinator->hasComponent<UserInterface>(entity))
            sprite.setColor({(sf::Uint8) ((float)r * cameraR), (sf::Uint8) ((float)g * cameraG), (sf::Uint8) ((float)b * cameraB), (sf::Uint8) (255 * spriteRenderer._opacity)});
        else
            sprite.setColor({(sf::Uint8) r, (sf::Uint8) g, (sf::Uint8) b, (sf::Uint8) (255 * spriteRenderer._opacity)});
        if (spriteRenderer._overlay) {
            sf::Sprite overlay = sprite;

            overlay.setScale({transform._width * (spriteRenderer._isFlippedHorizontally ? -1 : 1) * 1.1f, transform._height * (spriteRenderer._isFlippedVertically ? -1 : 1) * 1.1f});

            sf::Shader shader;
            if (!shader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
                std::cerr << "Shader loaded" << std::endl;
            shader.setUniform("texture", sf::Shader::CurrentTexture);
            coordinator->_window->draw(overlay, &shader);
        }
        coordinator->_window->draw(sprite);
    }
}

//TODO : if a movement is done, check the next in the queue, see if the pos in Y has changed

void DrawSystem::addedEntity(Entity entity) //place the entity in the right position in the vector
{
    int indexEnd = _entities.size() - 1;
    int newIndex = 0;
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    if (!coordinator->hasComponent<SpriteRenderer>(entity) || !coordinator->hasComponent<Transform>(entity))
        return;
    auto &spriteRenderer1 = coordinator->getComponent<SpriteRenderer>(entity);
    auto &transform1 = coordinator->getComponent<Transform>(entity);

    for (int i = indexEnd - 1; i >= 0; i--) {
        auto &spriteRenderer2 = coordinator->getComponent<SpriteRenderer>(_entities[i]);

        if (spriteRenderer1._layer > spriteRenderer2._layer) {
            newIndex = i + 1;
            break;
        } else if (spriteRenderer1._layer == spriteRenderer2._layer) {
            auto &transform2 = coordinator->getComponent<Transform>(_entities[i]);

            if (transform1._y > transform2._y) {
                newIndex = i + 1;
                break;
            }
        }
    }

    for (int i = indexEnd; i > newIndex; i--)
        _entities[i] = _entities[i - 1];
    _entities[newIndex] = entity;
}

void DrawSystem::layerChanged(Entity entity)
{
    int index = NULL_ENTITY;

    for (int i = 0; i < _entities.size(); i++) {
        if (_entities[i] == entity) {
            index = i;
            break;
        }
    }
    if (index == NULL_ENTITY)
        return;
    int i = index;
    for (; i < _entities.size() - 1; i++)
        _entities[i] = _entities[i + 1];
    _entities[i] = entity;
    addedEntity(entity);
}

void DrawSystem::yChanged(Entity entity)
{
    int index = NULL_ENTITY;

    for (int i = 0; i < _entities.size(); i++) {
        if (_entities[i] == entity) {
            index = i;
            break;
        }
    }
    if (index == NULL_ENTITY)
        return;

    int y = getCoordinator()->getComponent<Transform>(entity)._y;
    int layer = getCoordinator()->getComponent<SpriteRenderer>(entity)._layer;
    for (int i = index; i < _entities.size() - 1; i++) {
        int y2 = getCoordinator()->getComponent<Transform>(_entities[i + 1])._y;
        int layer2 = getCoordinator()->getComponent<SpriteRenderer>(_entities[i + 1])._layer;
        if (layer != layer2)
            break;
        if (y > y2) {
            _entities[i] = _entities[i + 1];
            _entities[i + 1] = entity;
            index = i;
        } else
            break;
    }
    for (int i = index; i > 0; i--) {
        int y2 = getCoordinator()->getComponent<Transform>(_entities[i - 1])._y;
        int layer2 = getCoordinator()->getComponent<SpriteRenderer>(_entities[i - 1])._layer;
        if (layer != layer2)
            break;
        if (y < y2) {
            _entities[i] = _entities[i - 1];
            _entities[i - 1] = entity;
        } else
            break;
    }
}

void DrawSystem::removedEntity(Entity entity)
{

}
