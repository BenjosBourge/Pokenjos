/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../include/components/playerController.hpp"


PlayerController::PlayerController()
{
    _isMoving = false;
    _tileX = 0;
    _tileY = 0;
    _initialTileX = 0;
    _initialTileY = 0;
    _timerMove = 0.0f;
}

PlayerController::~PlayerController()
{

}
