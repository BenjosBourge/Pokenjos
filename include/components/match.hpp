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

class Match {
public:
    Match();
    ~Match();

    Entity _selfEntity;
    void setSelfEntity(Entity entity) { _selfEntity = entity; }

    void launchNewMatch(std::vector<Entity> trainersPlayer, std::vector<Entity> trainersOpponent);

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

    float _loopingTimer;
};