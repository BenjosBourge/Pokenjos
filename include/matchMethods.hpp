/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once

void match_attackAnimation(Entity match, float deltaTime);
void match_showAttacks(Entity match);
void match_attackAnimationFinished(Entity match);
void match_launchAttack(Entity self);

void match_encounterAnimation(Entity match, float deltaTime);
void match_encounterAnimationFinished(Entity match);
void match_showPokemonInfos();
void match_removePokemonInfos();

void match_setLifeBarSize(Entity lifeBar, Entity trainer);