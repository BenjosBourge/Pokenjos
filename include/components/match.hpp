/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include <string>
#include <array>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "../core/entity.hpp"

enum MatchState {
    MATCH_STATE_START,
    MATCH_STATE_CHOOSE_ACTION,
    MATCH_STATE_START_ATTACK_PHASE,
    MATCH_STATE_ATTACK_PHASE,
    MATCH_STATE_HIT_FEEDBACK,
    MATCH_STATE_HIT_PHASE,
    MATCH_STATE_END
};

enum MatchMenu {
    MATCH_MENU_MAIN,
    MATCH_MENU_ATTACK,
    MATCH_MENU_POKEMON,
    MATCH_MENU_ITEM,
    MATCH_MENU_RUN
};

enum MatchAction {
    MATCH_ACTION_ATTACK,
    MATCH_ACTION_POKEMON,
    MATCH_ACTION_ITEM,
    MATCH_ACTION_RUN
};

class Trainer;

class Match {
public:
    Match();
    ~Match();

    Entity _selfEntity;
    void setSelfEntity(Entity entity) { _selfEntity = entity; }

    void launchNewMatch(std::vector<Entity> trainersPlayer, std::vector<Entity> trainersOpponent);
    void enemyPokemonAction();

    std::vector<Entity> _trainersPlayer;
    std::vector<Entity> _trainersOpponent;

    Entity _spritePlayer;
    Entity _spriteOpponent;

    Entity _spritePlayerBase;
    Entity _spriteOpponentBase;

    float _timeAnimation;
    void (*_animation)(Entity, float);
    void (*_animationEnded)(Entity);
    void setAnimation(void (*animation)(Entity, float), void (*animationEnded)(Entity));

    int _state;

    //action: (attacker, defender, action_type, id)
    std::vector<std::tuple<Entity, Entity, int, int>> _actionsInQueue;
    std::vector<std::tuple<Entity, Entity, int, int>> _actions;

    float _loopingTimer;

    int _itemCategory;
};