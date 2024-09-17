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
#include "../core/entity.hpp"

enum MatchState {
    MATCH_STATE_START,
    MATCH_STATE_CHOOSE_ACTION,
    MATCH_STATE_IN_TURN,
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

    float _timeAnimation;
    void (*_animation)(Entity, float);
    void (*_animationEnded)(Entity);
    void setAnimation(void (*animation)(Entity, float), void (*animationEnded)(Entity));

    int _state;
};