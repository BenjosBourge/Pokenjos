/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include <cmath>
//cannot change the header file
#include "../../../include/components/match.hpp"
#include "../../../include/core/coordinator.hpp"
#include "../../../include/core/components/spriteRenderer.hpp"
#include "../../../include/components/trainer.hpp"


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
}

Match::~Match()
{

}

void Match::setAnimation(void (*animation)(Entity, float), void (*animationEnded)(Entity)) {
    _animation = animation;
    _animationEnded = animationEnded;
}

void Match::launchNewMatch(std::vector<Entity> trainersPlayer, std::vector<Entity> trainersOpponent)
{
    _trainersPlayer = trainersPlayer;
    _trainersOpponent = trainersOpponent;
    _state = MATCH_STATE_START;
    _timeAnimation = 2.0f;

    //set the sprites
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    auto &spritePlayer = coordinator->getComponent<SpriteRenderer>(_spritePlayer);
    auto &spriteOpponent = coordinator->getComponent<SpriteRenderer>(_spriteOpponent);

    spritePlayer._texture = TEXTURE_TYPE_POKEMON_SPRITES_BACK;
    spritePlayer._rectWidth = 80;
    spritePlayer._rectHeight = 80;
    auto &trainerComponent = coordinator->getComponent<Trainer>(_trainersPlayer[0]);
    spritePlayer._offsetX = trainerComponent._pokemons[0]._id * 80;
    std::cout << trainerComponent._pokemons[0]._id << std::endl;

    spriteOpponent._texture = TEXTURE_TYPE_POKEMON_SPRITES;
    spriteOpponent._rectWidth = 80;
    spriteOpponent._rectHeight = 80;
    auto &enemyTrainerComponent = coordinator->getComponent<Trainer>(_trainersOpponent[0]);
    spriteOpponent._offsetX = enemyTrainerComponent._pokemons[0]._id * 80;
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
