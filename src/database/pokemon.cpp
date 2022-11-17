#include "database/dbpokemon.h"
#include "pokemon.h"

Pokemon FetchPokemon() {
    Stats stats = {1, 1, 1, 1 ,1 ,1};
    ElementType types[2];
    types[0] = FLYING;
    MoveSet moveset = {Move("move1", GROUND, 5, 50, 100)};

    return Pokemon("pokeman_test", stats, types, moveset);
}