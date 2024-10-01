/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../include/core/coordinator.hpp"
#include "../include/core/components/transform.hpp"
#include "../include/prefabPokemon.hpp"
#include "../include/components/match.hpp"
#include "../include/matchMethods.hpp"
#include "../include/core/myMath.hpp"
#include "../include/components/pokemon.hpp"
#include "../include/components/trainer.hpp"

int match_getPokeballBaseChance(Pokemon pokemon, int catchBonus)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    int baseCatchRate = 45;//TODO:pokemonComponent._baseCatchRate;
    int x = baseCatchRate * catchBonus;
    x *= (3 * pokemon._currentMaxHP - 2 * pokemon._currentHP);
    x /= (3 * pokemon._currentMaxHP);
    x *= 1; //TODO:STATUS

    if (x > 255)
        x = 255;
    if (x < 1)
        x = 1;
    return x;
}

int match_getPokeballAlteredChance(int x)
{
    if (x >= 255)
        return 65536; //always catch: 65535 + 1
    if (x <= 0)
        x = 1;
    double t = 16711680.0 / (double)x;
    t = my_sqrt(t);
    t = my_sqrt(t);
    double y = 1048560.0 / t;
    return (int)y;
}

bool match_isPokeballCaught(int y)
{
    int r = rand() % 65536;
    std::cout << "r: " << r << " y: " << y << std::endl;
    return r <= y;
}

void match_throwPokeball()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");
    auto &matchComponent = coordinator->getComponent<Match>(match);

    Entity trainerOpponent = matchComponent._trainersOpponent[0];
    auto &trainerOpponentComponent = coordinator->getComponent<Trainer>(trainerOpponent);
    Pokemon pokemon = trainerOpponentComponent._pokemons[0];

    int x = match_getPokeballBaseChance(pokemon, 1); //no catch bonus, need the pokeball id
    int y = match_getPokeballAlteredChance(x);

    matchComponent._YCatchValue = y;
    matchComponent._twitchValue = 0;
}
