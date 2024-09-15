/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include <cmath>
#include "../../../include/components/pokemon.hpp"


Attack::Attack()
{
    _id = -1;
    _name = "MissingAtk";
    _type = NONE_TYPE;
    _power = 1;
    _accuracy = 1;
    _pp = 1;
    _effect = nullptr;
}

Attack::Attack(std::string name, int id, int type, int category, int power, int accuracy, int pp) : Attack() {
    _name = name;
    _id = id;
    _type = type;
    _category = category;
    _power = power;
    _accuracy = accuracy;
    _pp = pp;
}

Attack::Attack(std::string name, int id, int type, int category, int power, int accuracy, int pp, void (*effect)(Pokemon *, Pokemon *)) : Attack()
{
    _name = name;
    _id = id;
    _type = type;
    _category = category;
    _power = power;
    _accuracy = accuracy;
    _pp = pp;
    _effect = effect;
}

Attack::~Attack()
{

}

Pokemon::Pokemon()
{
    /*base stats*/
    _hp = 1;
    _attack = 1;
    _defense = 1;
    _specialAttack = 1;
    _specialDefense = 1;
    _speed = 1;

    /*stats*/
    _currentHP = 1;
    _currentMaxHP = 1;
    _currentAttack = 1;
    _currentDefense = 1;
    _currentSpecialAttack = 1;
    _currentSpecialDefense = 1;
    _currentSpeed = 1;
    _level = 1;
    _xp = 0;
    _xpToNextLevel = 100;

    /*ids*/
    _id = -1;
    _name = "MissingNo";

    /*types*/
    _type1 = NORMAL_TYPE;
    _type2 = NONE_TYPE;

    /*attacks*/
    for (int i = 0; i < 4; i++) {
        _attacks[i] = Attack();
        _currentPP[i] = 1;
    }
}

Pokemon::Pokemon(std::string name, int id, int hp, int attack, int defense, int specialAttack, int specialDefense, int speed, Type type1, Type type2) : Pokemon()
{
    /*base stats*/
    _hp = hp;
    _attack = attack;
    _defense = defense;
    _specialAttack = specialAttack;
    _specialDefense = specialDefense;
    _speed = speed;

    /*ids*/
    _id = id;
    _name = name;

    /*types*/
    _type1 = type1;
    _type2 = type2;
}

Pokemon::~Pokemon()
{

}

int hpStatCalc(int baseStat, int iv, int ev, int level)
{
    return floor(0.01 * (2 * baseStat + iv + floor(0.25 * ev)) * level) + level + 10;
}

int otherStatCalc(int baseStat, int iv, int ev, int level)
{
    return floor(0.01 * (2 * baseStat + iv + floor(0.25 * ev)) * level) + 5;
}

void Pokemon::resetStats()
{
    //to grow with the growth of the max hp
    int diffHP = _currentMaxHP - _currentHP;

    _currentMaxHP = hpStatCalc(_hp, 0, 0, _level);
    _currentHP = _currentMaxHP - diffHP;

    _currentAttack = otherStatCalc(_attack, 0, 0, _level);
    _currentDefense = otherStatCalc(_defense, 0, 0, _level);
    _currentSpecialAttack = otherStatCalc(_specialAttack, 0, 0, _level);
    _currentSpecialDefense = otherStatCalc(_specialDefense, 0, 0, _level);
    _currentSpeed = otherStatCalc(_speed, 0, 0, _level);
}

void Pokemon::changeToPokemon(int id)
{
    //Only stats are changed, not the attacks
    Pokemon newPokemon = getPokemon(id);

    _id = newPokemon._id;
    _name = newPokemon._name;
    _hp = newPokemon._hp;
    _attack = newPokemon._attack;
    _defense = newPokemon._defense;
    _specialAttack = newPokemon._specialAttack;
    _specialDefense = newPokemon._specialDefense;
    _speed = newPokemon._speed;
    _type1 = newPokemon._type1;
    _type2 = newPokemon._type2;
}

void Pokemon::gainXP(int xp)
{
    _xp += xp;
    while (_xp >= _xpToNextLevel) {
        _level += 1;
        _xpToNextLevel = (_level+1) * (_level+1) * (_level+1);

        levelUp();
    }

    //check evolution
    int evolution = getEvolutionFromId(_id, _level);
    if (evolution != -1) {
        changeToPokemon(_id + 1);
        resetStats();
    }
}

void Pokemon::levelUp()
{
    //learn new attacks
    Attack newAttack = getAttackAtLevel(_level);

    //reset stats
    resetStats();
}