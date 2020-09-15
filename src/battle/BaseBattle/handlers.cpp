#include <stdexcept> // for runtime_error

#include "pokemon/battle/baseBattle.h" // for BaseBattle
#include "pokemon/player.h"            // for UID

void BaseBattle::HandleRoundStart() {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::HandleRoundEnd() {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::SwapPokemon(UID uid, int index) {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::ApplyMoves() { throw std::runtime_error("Not Implemented"); }