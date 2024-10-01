/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include <cmath>
//cannot change the header file
#include "../../../include/components/match.hpp"
#include "../../../include/core/coordinator.hpp"
#include "../../../include/core/components/spriteRenderer.hpp"
#include "../../../include/components/trainer.hpp"
#include "../../../include/matchMethods.hpp"
#include "../../../include/core/components/tag.hpp"
#include "../../../include/core/components/text.hpp"
#include "../../../include/core/components/transform.hpp"
#include "../../../include/core/components/ui.hpp"


Match::Match()
{
    _selfEntity = NULL_ENTITY;
    _trainersPlayer = std::vector<Entity>();
    _trainersOpponent = std::vector<Entity>();

    _spritePlayer = NULL_ENTITY;
    _spriteOpponent = NULL_ENTITY;
    _spritePlayerBase = NULL_ENTITY;
    _spriteOpponentBase = NULL_ENTITY;

    _state = MATCH_STATE_START;

    _timeAnimation = 0.0f;
    _animation = nullptr;
    _animationEnded = nullptr;

    _loopingTimer = 0.0f;

    _itemCategory = 0;
    _YCatchValue = 0;
    _twitchValue = 0;
}

Match::~Match()
{

}

void Match::setAnimation(void (*animation)(Entity, float), void (*animationEnded)(Entity)) {
    _animation = animation;
    _animationEnded = animationEnded;
}

void Match::exitMatch()
{
    std::cout << "Exit Match" << std::endl;
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    _inMatch = false;
    match_removePokemonInfos();
    match_removeItemButtons();
    _actionsInQueue.clear();
    coordinator->removeEntitiesFromTag("main_menu");
    coordinator->removeEntitiesFromTag("menu_bag");
    coordinator->removeEntitiesFromTag("playerSprite");
    coordinator->removeEntitiesFromTag("enemySprite");
    coordinator->removeEntitiesFromTag("playerSpriteBase");
    coordinator->removeEntitiesFromTag("enemySpriteBase");
    coordinator->removeEntitiesFromTag("menu_background");
}

void Match::launchNewMatch(std::vector<Entity> trainersPlayer, std::vector<Entity> trainersOpponent)
{
    _inMatch = true;

    _trainersPlayer = trainersPlayer;
    _trainersOpponent = trainersOpponent;
    _state = MATCH_STATE_START;
    _timeAnimation = 2.0f;

    //set the sprites
    std::shared_ptr<Coordinator> coordinator = getCoordinator();


    //player sprites
    Entity playerSprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerSprite, Transform(0, -100, 5, 5));
    coordinator->addComponent<SpriteRenderer>(playerSprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 1));
    coordinator->addComponent<Tag>(playerSprite, Tag("playerSprite"));

    Entity enemySprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemySprite, Transform(0, -250, 5, 5));
    coordinator->addComponent<SpriteRenderer>(enemySprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 1));
    coordinator->addComponent<Tag>(enemySprite, Tag("enemySprite"));

    _spritePlayer = playerSprite;
    _spriteOpponent = enemySprite;

    auto &spritePlayer = coordinator->getComponent<SpriteRenderer>(playerSprite);
    auto &spriteOpponent = coordinator->getComponent<SpriteRenderer>(enemySprite);

    spritePlayer._texture = TEXTURE_TYPE_POKEMON_SPRITES_BACK;
    spritePlayer._rectWidth = 80;
    spritePlayer._rectHeight = 80;
    auto &trainerComponent = coordinator->getComponent<Trainer>(_trainersPlayer[0]);
    spritePlayer._offsetX = trainerComponent._pokemons[0]._id * 80;
    trainerComponent._spriteLinked = playerSprite;

    spriteOpponent._texture = TEXTURE_TYPE_POKEMON_SPRITES;
    spriteOpponent._rectWidth = 80;
    spriteOpponent._rectHeight = 80;
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(_trainersOpponent[0]);
    spriteOpponent._offsetX = enemyTrainerComponent._pokemons[0]._id * 80;
    enemyTrainerComponent._spriteLinked = enemySprite;


    Entity playerSpriteBase = coordinator->createEntity();
    coordinator->addComponent<Transform>(playerSpriteBase, Transform(0, 40, 5, 5));
    coordinator->addComponent<SpriteRenderer>(playerSpriteBase, SpriteRenderer(TEXTURE_TYPE_PLAYER_BASE, 204, 30, 0));
    coordinator->addComponent<Tag>(playerSpriteBase, Tag("playerSpriteBase"));

    Entity enemySpriteBase = coordinator->createEntity();
    coordinator->addComponent<Transform>(enemySpriteBase, Transform(0, -110, 5, 5));
    coordinator->addComponent<SpriteRenderer>(enemySpriteBase, SpriteRenderer(TEXTURE_TYPE_ENEMY_BASE, 126, 32, 0));
    coordinator->addComponent<Tag>(enemySpriteBase, Tag("enemySpriteBase"));

    _spritePlayerBase = playerSpriteBase;
    _spriteOpponentBase = enemySpriteBase;

    setAnimation(match_encounterAnimation, match_encounterAnimationFinished);

    Entity MenuSprite = coordinator->createEntity();
    coordinator->addComponent<Transform>(MenuSprite, Transform(0, 355, 62, 16));
    coordinator->addComponent<SpriteRenderer>(MenuSprite, SpriteRenderer(TEXTURE_TYPE_EXAMPLE, 32, 32, 3));
    auto &MenuSpriteComponent = coordinator->getComponent<SpriteRenderer>(MenuSprite);
    MenuSpriteComponent._color = sf::Color(150, 150, 150);
    coordinator->addComponent<Tag>(MenuSprite, Tag("menu_background"));

    Entity TextMenu = coordinator->createEntity();
    coordinator->addComponent<Transform>(TextMenu, Transform(-400, 250, 62, 16));
    coordinator->addComponent<UserInterface>(TextMenu);
    coordinator->addComponent<Tag>(TextMenu, Tag("textMenu"));
    coordinator->addComponent<Text>(TextMenu, Text("", 64, sf::Color::White));
}

void Match::enemyPokemonAction()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto &trainer : _trainersOpponent) {
        auto &trainerComponent = coordinator->getComponent<Trainer>(trainer);

        //TODO: choose the best action

        if (trainerComponent._pokemons[0]._currentHP > 0) {
            _actionsInQueue.push_back(std::make_tuple(trainer, _trainersPlayer[0], MATCH_ACTION_ATTACK, 0));
            break;
        }
    }
}
