/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once

void match_attackAnimation(Entity match, float deltaTime);
void match_showAttacks(Entity match);
void match_attackAnimationFinished(Entity match);
void match_launchAttack(Entity self);

void match_startAnimation(Entity match, float deltaTime);
void match_startAnimationFinished(Entity match);
void match_showPokemonInfos();
void match_removePokemonInfos();