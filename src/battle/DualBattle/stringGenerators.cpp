#include <sstream> // for operator<<, basic_ostream
#include <string>  // for allocator, operator+, char_tr...
#include <vector>  // for vector

#include "pokemon/battle/dualBattle.h" // for DualBattle
#include "pokemon/moves.h"             // for Move
#include "pokemon/player.h"            // for Player
#include "pokemon/pokemon.h"           // for Pokemon, MoveSet

std::string DualBattle::generateMoveSummary(Player player) {
  auto moveset = player.Team[0]->Moveset;
  return "Move 1: " + moveset.move1.GetName() + "\n" +
         "Move 2: " + moveset.move2.GetName() + "\n" +
         "Move 3: " + moveset.move3.GetName() + "\n" +
         "Move 4: " + moveset.move4.GetName();
}

std::string DualBattle::generateSwapSummary(Player player) {
  // TODO: Generate swap summary
  return "keks";
}

std::string DualBattle::generateBattleSummary() {
  std::stringstream ret;
  ret << this->player1->Name << "'s " << this->player1->Team[0]->Nickname
      << " Health: " << this->player1->Team[0]->Health;
  ret << std::endl;
  ret << this->player2->Name << "'s " << this->player2->Team[0]->Nickname
      << " Health: " << this->player2->Team[0]->Health;

  return ret.str();
}