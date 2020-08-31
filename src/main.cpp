#include <iostream>
#include <Windows.h>
#include "player.h"
#include "pokemon.h"
#include "battleHolder.h"

int main(int argc, char const *argv[])
{
    Stats stats = {1, 1, 1, 1 ,1 ,1};
    ElementType types[2];
    types[0] = FLYING;
    Move moveset[4] = {Move("move1", GROUND, 5, 50, 100)};

    Pokemon pokemon1("pokeman", stats, types, moveset);
    Player player1("1", "player1", MALE);
    player1.addPokemonInTeam(pokemon1);

    Pokemon pokemon2("pokeman", stats, types, moveset);
    Player player2("2", "player2", FEMALE);
    player2.addPokemonInTeam(pokemon2);

    BattleHolder battle(player1, player2);
    //std::cout << battle.FirstMove().getUID();

    system("Pause");
}
