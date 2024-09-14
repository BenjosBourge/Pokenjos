/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/lifeTimer.hpp"

LifeTimer::LifeTimer()
{
    _lifeTime = 1;
    _maxLifeTime = 1;
    _decreasingOpacity = false;
}

LifeTimer::LifeTimer(float lifeTime)
{
    _lifeTime = lifeTime;
    _maxLifeTime = lifeTime;
    _decreasingOpacity = false;
}

LifeTimer::LifeTimer(float lifeTime, bool opacity)
{
    _lifeTime = lifeTime;
    _maxLifeTime = lifeTime;
    _decreasingOpacity = opacity;
}

LifeTimer::~LifeTimer()
{

}
