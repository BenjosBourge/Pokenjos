/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include "enumPokemon.hpp"


/*
 * <Level, Attack>
 *
 * When a Pokemon levels up, it can learn the level 0 attack.
 */

const std::pair<int, AttackId> tableBulbasaur[] =
        {
                {1, TACKLE},
                {1, GROWL},
                {3, VINE_WHIP},
                {6, GROWTH},
                {9, LEECH_SEED},
                {12, RAZOR_LEAF},
                {15, POISON_POWDER},
                {15, SLEEP_POWDER},
                //{18, SEED_BOMB},
                {21, TAKE_DOWN},
                //{24, SWEET_SCENT},
                //{27, SYNTHESIS},
                //{30, WORRY_SEED},
                //{33, POWER_WHIP},
                {36, SOLAR_BEAM}
        };

const std::pair<int, AttackId> tableIvysaur[] =
        {
                {1, TACKLE},
                {1, GROWL},
                {1, VINE_WHIP},
                {1, GROWTH},
                {9, LEECH_SEED},
                {12, RAZOR_LEAF},
                {15, POISON_POWDER},
                {15, SLEEP_POWDER},
                //{20, SEED_BOMB},
                {25, TAKE_DOWN},
                //{30, SWEET_SCENT},
                //{35, SYNTHESIS},
                //{40, WORRY_SEED},
                //{45, POWER_WHIP},
                {50, SOLAR_BEAM}
        };

const std::pair<int, AttackId> tableVenusaur[] =
        {
                //{0, PETAL_BLIZZARD},
                {1, PETAL_DANCE},
                {1, TACKLE},
                {1, GROWL},
                {1, VINE_WHIP},
                {1, GROWTH},
                {9, LEECH_SEED},
                {12, RAZOR_LEAF},
                {15, POISON_POWDER},
                {15, SLEEP_POWDER},
                //{20, SEED_BOMB},
                {25, TAKE_DOWN},
                //{30, SWEET_SCENT},
                //{37, SYNTHESIS},
                //{44, WORRY_SEED},
                //{51, POWER_WHIP},
                {58, SOLAR_BEAM}
        };

const std::pair<int, AttackId> tableCharmander[] =
        {
                {1, SCRATCH},
                {1, GROWL},
                {4, EMBER},
                //{8, SMOKE_SCREEN},
                //{12, DRAGON_BREATH},
                //{17, FIRE_FANG},
                {20, SLASH},
                {24, FLAMETHROWER},
                //{28, SCARY_FACE},
                {32, FIRE_SPIN},
                //{36, INFERNO},
                //{40, FLARE_BLITZ}
        };

const std::pair<int, AttackId> tableCharmeleon[] =
        {
                {1, SCRATCH},
                {1, GROWL},
                {1, EMBER},
                //{1, SMOKE_SCREEN},
                //{12, DRAGON_BREATH},
                //{19, FIRE_FANG},
                {24, SLASH},
                {30, FLAMETHROWER},
                //{37, SCARY_FACE},
                //{48, INFERNO},
                //{54, FLARE_BLITZ}
        };

const std::pair<int, AttackId> tableCharizard[] =
        {
                //{0, DRAGON_SLASH}
                //{1, DRAGON_CLAW},
                {1, SCRATCH},
                {1, GROWL},
                {1, EMBER},
                //{HEAT_WAVE},
                //{1, SMOKE_SCREEN},
                //{12, DRAGON_BREATH},
                //{19, FIRE_FANG},
                {24, SLASH},
                {30, FLAMETHROWER},
                //{39, SCARY_FACE},
                //{54, INFERNO},
                //{62, FLARE_BLITZ}
        };

const std::pair<int, AttackId> tableSquirtle[] =
        {
                {1, TACKLE},
                {1, TAIL_WHIP},
                {3, WATER_GUN},
                {6, WITHDRAW},
                //{9, RAPID_SPIN},
                {12, BITE},
                //{15, WATER_PULSE},
                //{18, PROTECT},
                //{21, RAIN_DANCE},
                //{24, AQUA_TAIL},
                //{27, SHELL_SMASH},
                //{30, IRON_DEFENSE},
                {33, HYDRO_PUMP},
                //{36, WAVE_CRASH}
        };

const std::pair<int, AttackId> tableWartortle[] =
        {
                {1, TACKLE},
                {1, TAIL_WHIP},
                {1, WATER_GUN},
                {1, WITHDRAW},
                //{9, RAPID_SPIN},
                {12, BITE},
                //{15, WATER_PULSE},
                //{20, PROTECT},
                //{25, RAIN_DANCE},
                //{30, AQUA_TAIL},
                //{35, SHELL_SMASH},
                //{40, IRON_DEFENSE},
                {45, HYDRO_PUMP},
                //{50, WAVE_CRASH}
        };

const std::pair<int, AttackId> tableBlastoise[] =
        {
                //{0, FLASH_CANNON},
                {1, TACKLE},
                {1, TAIL_WHIP},
                {1, WATER_GUN},
                {1, WITHDRAW},
                //{9, RAPID_SPIN},
                {12, BITE},
                //{15, WATER_PULSE},
                //{20, PROTECT},
                //{25, RAIN_DANCE},
                //{30, AQUA_TAIL},
                //{35, SHELL_SMASH},
                //{42, IRON_DEFENSE},
                {49, HYDRO_PUMP},
                //{56, WAVE_CRASH}
        };