#include "pokemon.h"
#include "moves.h"

Pokemon::Pokemon(std::string name, Stats stats, ElementType types[2], Move moveset[]) {
    Pokemon::Nickname = name;
    Pokemon::baseStats = stats;
    Pokemon::MoveSet = moveset;

    for (int i = 0; i < 2; i++) {
        Pokemon::type[i] = types[i];
    }
};

std::string Pokemon::getNickname() {
    return this->Nickname;
}