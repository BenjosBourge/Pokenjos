/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/trail.hpp"

Trail::Trail()
{
    _isActive = true;
    _timerSpawn = 0.1f;
    _currentTimerSpawn = 0.1f;
}

Trail::Trail(float timerSpawn)
{
    _isActive = true;
    _timerSpawn = timerSpawn;
    _currentTimerSpawn = timerSpawn;
}

Trail::~Trail()
{

}
