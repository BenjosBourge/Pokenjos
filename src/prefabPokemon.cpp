/*------------------------*
 * Pokenjos by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include <vector>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "../include/prefabPokemon.hpp"

Pokemon getPokemonFromId(PokemonId id)
{
    Pokemon pokemon = pokemonArray[id];

    return pokemon;
}

Pokemon createPokemon(PokemonId id, int level)
{
    Pokemon pokemon = getPokemonFromId(id);

    pokemon._level = level;
    pokemon._currentHP = pokemon._hp;

    //set the attacks

    return pokemon;
}

std::vector<Pokemon> getAllPokemonsFromType(Type type)
{
    std::vector<Pokemon> pokemons;

    for (const auto & i : pokemonArray)
        if (i._type1 == type || i._type2 == type)
            pokemons.push_back(i);

    return pokemons;
}

Attack getAttackFromId(AttackId id)
{
    Attack attack = attackArray[id];

    return attack;
}

std::vector<Attack> getAllAttacksFromType(Type type)
{
    std::vector<Attack> attacks;

    for (const auto & i : attackArray)
        if (i._type == type)
            attacks.push_back(i);

    return attacks;
}