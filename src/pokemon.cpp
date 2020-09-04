#include "pokemon.h"
#include "moves.h"

Pokemon::Pokemon(std::string name, Stats stats, ElementType types[2], MoveSet moveset) {
    this->Nickname = name;
    this->baseStats = stats;
    this->Moveset = moveset;
    this->Health = stats.MaxHP;

    for (int i = 0; i < 2; i++) {
        this->type[i] = types[i];
    }
}

Pokemon::Pokemon() {
    this->Nickname = "";
    this->baseStats = Stats{};
    this->Moveset = MoveSet{};
    this->Health = 0;
    this->type[0] = NIL;
    this->isEmpty = true;
}