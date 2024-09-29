/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../include/core/coordinator.hpp"
#include "../include/core/components/transform.hpp"
#include "../include/prefabPokemon.hpp"
#include "../include/components/match.hpp"
#include "../include/matchMethods.hpp"
#include "../include/core/myMath.hpp"

int match_getPokeballBaseChance(Entity pokemon, int catchBonus)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    auto &pokemonComponent = coordinator->getComponent<Pokemon>(pokemon);

    int baseCatchRate = 45;//TODO:pokemonComponent._baseCatchRate;
    int x = baseCatchRate * catchBonus;
    x *= (3 * pokemonComponent._currentMaxHP - 2 * pokemonComponent._currentHP);
    x /= (3 * pokemonComponent._currentMaxHP);
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
    return r <= y;
}

void match_throwPokeball()
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity match = coordinator->getEntityFromTag("match");
    auto &matchComponent = coordinator->getComponent<Match>(match);


}