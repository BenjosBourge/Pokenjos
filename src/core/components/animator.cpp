/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/animator.hpp"

Animator::Animator()
{
    _currentFrame = 0;
    _time = 0;
    _verticalOffset = 0;
}

Animator::Animator(Animation animation)
{
    _currentFrame = 0;
    _time = 0;
    _verticalOffset = 0;
    _currentAnimation = animation;
    _animations.push_back(animation);
}

Animator::~Animator()
{

}

void Animator::addAnimation(Animation animation)
{
    if (_animations.size() == 0)
        _currentAnimation = animation;
    _animations.push_back(animation);
}

Animation::Animation()
{
    _numberOfFrames = 0;
    _isLooping = false;
    _frameTime = 0;
}

Animation::Animation(int numberOfFrames, float frameTime)
{
    _numberOfFrames = numberOfFrames;
    _isLooping = true;
    _frameTime = frameTime;
}

Animation::Animation(int numberOfFrames, float frameTime, bool isLooping)
{
    _numberOfFrames = numberOfFrames;
    _isLooping = isLooping;
    _frameTime = frameTime;
}

Animation::~Animation()
{

}
