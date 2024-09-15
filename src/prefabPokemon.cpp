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
    pokemon._xp = level * level * level;
    pokemon._xpToNextLevel = (level + 1) * (level + 1) * (level + 1);

    //set the attacks
    auto table = tablePokemonAttack[pokemon._id];
    for (auto & i : table)
        if (i.first <= level) {
            bool found = false;
            for (int j = 0; j < 4; j += 1) {
                if (pokemon._attacks[j]._id == -1) {
                    pokemon._attacks[j] = getAttackFromId(i.second);
                    found = true;
                    break;
                }
            }
            if (!found) {
                int index = rand() % 6;

                if (index < 4)
                    pokemon._attacks[index] = getAttackFromId(i.second);
            }
        }
    pokemon.resetStats();
    pokemon._currentHP = pokemon._currentMaxHP;
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


/*
 * These functions are here because otherwise compilation wouldn't work.
 * Don't know why.
 */

int Pokemon::getEvolutionFromId(int id, int level)
{
    for (const auto & i : evolutionLvlTable)
        if (i.first == id && i.second <= level) {
            return id + 1;
        }
    return -1;
}

Attack Pokemon::getAttackAtLevel(int level)
{
    auto table = tablePokemonAttack[static_cast<PokemonId>(_id)];
    for (auto & i : table)
        if (i.first == _level) {
            return getAttackFromId(i.second);
        }
    return Attack();
}

Pokemon Pokemon::getPokemon(int id)
{
    return getPokemonFromId(static_cast<PokemonId>(id));
}