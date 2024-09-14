/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../../include/core/components/tag.hpp"

Tag::Tag()
{
    _tag = "default";
}

Tag::Tag(std::string tag)
{
    _tag = tag;
}

Tag::~Tag()
{

}
