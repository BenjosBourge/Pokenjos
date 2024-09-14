/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#pragma once
#include <bitset>

using Entity = unsigned int;
const Entity MAX_ENTITIES = 5000;
const Entity NULL_ENTITY = 5000;

const unsigned int MAX_COMPONENTS = 64;
using Signature = std::bitset<MAX_COMPONENTS>;
