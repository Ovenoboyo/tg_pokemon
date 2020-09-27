#include <sstream> // for operator<<, basic_ostream
#include <string>  // for allocator, operator+, char_tr...
#include <vector>  // for vector

#include "fmt/core.h"
#include "pokemon/battle/dualBattle.h" // for DualBattle
#include "pokemon/moves.h"             // for Move
#include "pokemon/pokemon.h"           // for Pokemon, MoveSet
#include "pokemon/user/player.h"       // for Player

std::string DualBattle::generateMoveSummary(Player player) {
    auto moveset = player.Team.at(0)->Moveset;
    std::string ret = "";
    int i = 0;
    for (auto m : moveset) {
        ret += fmt::format("Move {0}: {1}\n", i, m->GetName());
        i++;
    }
    return ret;
}

std::string DualBattle::generateSwapSummary(Player player) {
    // TODO: Generate swap summary
    return "keks";
}

std::string DualBattle::generateBattleSummary() {
    std::stringstream ret;
    ret << this->player1->Name << "'s " << this->player1->Team.at(0)->Nickname
        << " Health: " << this->player1->Team.at(0)->Health;
    ret << std::endl;
    ret << this->player2->Name << "'s " << this->player2->Team.at(0)->Nickname
        << " Health: " << this->player2->Team.at(0)->Health;

    return ret.str();
}