#include <stdexcept> // for runtime_error
#include <string>    // for string

#include "pokemon/battle/baseBattle.h" // for BaseBattle
#include "pokemon/player.h"            // for Player

std::string BaseBattle::generateBattleSummary() {
  throw std::runtime_error("Not Implemented");
}

std::string BaseBattle::generateMoveSummary(Player player) {
  throw std::runtime_error("Not Implemented");
}

std::string BaseBattle::generateSwapSummary(Player player) {
  throw std::runtime_error("Not Implemented");
}