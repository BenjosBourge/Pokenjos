/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../texture.hpp"

class Animation {
public:
    Animation();
    Animation(int numberOfFrames, float frameTime);
    Animation(int numberOfFrames, float frameTime, bool isLooping);
    ~Animation();

    int _numberOfFrames;
    bool _isLooping;
    float _frameTime;
};

class Animator {
public:
    Animator();
    Animator(Animation animation);
    ~Animator();

    std::vector<Animation> _animations;
    Animation _currentAnimation;
    float _time;
    int _currentFrame;
    int _verticalOffset;

    void addAnimation(Animation animation);
};
