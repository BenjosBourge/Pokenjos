/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../include/components/playerController.hpp"


PlayerController::PlayerController()
{
    _isMoving = false;
    _tileX = 10;
    _tileY = 10;
    _initialTileX = 10;
    _initialTileY = 10;
    _timerMove = 0.0f;
}

PlayerController::~PlayerController()
{

}
