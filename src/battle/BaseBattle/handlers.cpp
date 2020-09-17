#include <stdexcept> // for runtime_error

#include "pokemon/battle/baseBattle.h" // for BaseBattle
#include "pokemon/user/player.h"            // for UID

void BaseBattle::HandleRoundStart() {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::HandleRoundEnd() {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::HandleBattle(UID uid, int moveNo, bool swap) {
    this->HandlePlayerChoice(uid, moveNo, swap);
    this->HandleRoundEnd();
    this->HandleRoundStart();
}

void BaseBattle::HandleBattle() {
    this->HandleRoundStart();
}