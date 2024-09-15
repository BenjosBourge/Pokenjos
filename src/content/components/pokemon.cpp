/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../include/components/pokemon.hpp"


Attack::Attack()
{
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
