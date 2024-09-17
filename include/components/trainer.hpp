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

class Trainer {
public:
    Trainer();
    ~Trainer();

    std::string _name;
    std::array<Pokemon, 6> _pokemons;
    int _currentPokemon;
    int _money;
};