/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>

class PlayerController {
public:
    PlayerController();
    ~PlayerController();

    bool _isMoving;
    int _tileX;
    int _tileY;
    int _initialTileX;
    int _initialTileY;
    float _timerMove;
};