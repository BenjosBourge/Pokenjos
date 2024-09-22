/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include <string>
#include <array>
#include "pokemon.hpp"
#include "../core/entity.hpp"

class Trainer {
public:
    Trainer();
    ~Trainer();

    int _id = 0;
    std::string _name;
    std::array<Pokemon, 6> _pokemons;
    int _currentPokemon;
    int _money;

    Entity _spriteLinked;
};