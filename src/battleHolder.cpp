#include "battleHolder.h"
#include <iostream>
#include <time.h>

BattleHolder::BattleHolder(Player p1, Player p2) {
    this->Players[0] = p1;
    this->Players[1] = p2;

    for(int i = 0; i < 2; i++) {
        std::string uid = (i == 0) ? (p1.getUID()) : (p2.getUID());
        Pokemon *team = (i == 0) ? (p2.getTeam()) : (p2.getTeam());

        this->Pokemons.insert({uid, team});
        this->activePokemon.insert({uid, team[0]});
    }
}

Player BattleHolder::FirstMove() {
    srand(time(0));
    return this->Players[(std::rand() % 2)];
}