/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include "components/pokemon.hpp"

void exitMatch();
void startMatch(std::vector<Entity> trainersPlayer, std::vector<Entity> trainersOpponent);

void match_setupCombatSequence();

void match_attackAnimation(Entity match, float deltaTime);
void match_showMain();
void match_attackAnimationFinished(Entity match);
void match_launchAttack(Entity self);

void match_encounterAnimation(Entity match, float deltaTime);
void match_encounterAnimationFinished(Entity match);
void match_showPokemonInfos();
void match_removePokemonInfos();
void match_removeItemButtons();

void match_setLifeBarSize(Entity lifeBar, Entity trainer);

/*Pokeballs*/
int match_getPokeballBaseChance(Pokemon pokemon, int catchBonus);
int match_getPokeballAlteredChance(int x);
bool match_isPokeballCaught(int y);
void match_throwPokeball();