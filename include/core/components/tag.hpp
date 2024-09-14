/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include <string>

class Tag {
public:
    Tag();
    Tag(std::string tag);
    ~Tag();

    std::string _tag;
};
