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
#include <SFML/Graphics.hpp>

//needs to be here

enum Type {
    NORMAL_TYPE,
    FIRE_TYPE,
    WATER_TYPE,
    ELECTRIC_TYPE,
    GRASS_TYPE,
    ICE_TYPE,
    FIGHTING_TYPE,
    POISON_TYPE,
    GROUND_TYPE,
    FLYING_TYPE,
    PSYCHIC_TYPE,
    BUG_TYPE,
    ROCK_TYPE,
    GHOST_TYPE,
    DRAGON_TYPE,
    DARK_TYPE,
    STEEL_TYPE,
    FAIRY_TYPE,
    NONE_TYPE
};

static const std::vector<sf::Color> type_colors = {
        {176, 176, 160}, //NORMAL
        {240, 0, 0}, //FIRE
        {121, 176, 248}, //WATER
        {248, 248, 62}, //ELECTRIC
        {112, 216, 80}, //GRASS
        {160, 248, 248}, //ICE
        {208, 124, 36}, //COMBAT
        {138, 97, 174}, //POISON
        {208, 176, 96}, //GROUND
        {176, 176, 186}, //FLYING
        {248, 88, 184}, //PSYCHIC
        {112, 216, 80}, //BUG
        {160, 104, 80}, //ROCK
        {168, 112, 208}, //GHOST
        {105, 68, 137}, //DRAGON
        {60, 49, 70}, //DARK
        {144, 168, 180}, //STEEL
        {231, 141, 186}, //FAIRY
        {0, 0, 0} //NONE

};

class Pokemon;

class Attack {
public:
    Attack();
    Attack(std::string name, int id, int type, int category, int power, int accuracy, int pp);
    Attack(std::string name, int id, int type, int category, int power, int accuracy, int pp, void (*effect)(Pokemon* attacker, Pokemon* defender));
    ~Attack();

    int _id;
    std::string _name;
    int _type;
    int _category;
    int _power;
    int _accuracy;
    int _pp;
    void (*_effect)(Pokemon* attacker, Pokemon* defender);
};

class Pokemon {
public:
    Pokemon();
    Pokemon(std::string name, int id, int hp, int attack, int defense, int specialAttack, int specialDefense, int speed, Type type1, Type type2);
    ~Pokemon();

    void resetStats();

    void changeToPokemon(int id);
    void gainXP(int xp);
    void levelUp();

    bool _isCaptured;

    int _pvToGo;
    int _pvFrom;

    int _currentHP;
    int _currentMaxHP;
    int _currentAttack;
    int _currentDefense;
    int _currentSpecialAttack;
    int _currentSpecialDefense;
    int _currentSpeed;
    int _level;
    int _xp;
    int _xpToNextLevel;

    int _id;
    std::string _name;

    int _hp;
    int _attack;
    int _defense;
    int _specialAttack;
    int _specialDefense;
    int _speed;

    int _type1;
    int _type2;

    std::array<Attack, 4> _attacks;
    std::array<int, 4> _currentPP;

    /*in prefab*/
    Attack getAttackAtLevel(int level);
    Pokemon getPokemon(int id);
    int getEvolutionFromId(int id, int level);
};
