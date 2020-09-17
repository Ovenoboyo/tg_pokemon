#include <sstream> // for operator<<, basic_ostream
#include <string>  // for allocator, operator+, char_tr...
#include <vector>  // for vector

#include "fmt/core.h"
#include "pokemon/battle/wildBattle.h" // for WildBattle
#include "pokemon/moves.h"             // for Move
#include "pokemon/user/player.h"            // for Player
#include "pokemon/pokemon.h"           // for Pokemon, MoveSet

std::string WildBattle::generateMoveSummary(Player player) {
    auto moveset = player.Team.at(0)->Moveset;
    std::string ret = "Move 1: {} \nMove 2: {}\nMove 3: {}\nMove 4: {}";
    return fmt::format(ret, moveset.at(0)->GetName(), moveset.at(1)->GetName(),
                       moveset.at(2)->GetName(), moveset.at(3)->GetName());
}

std::string WildBattle::generateSwapSummary(Player player) {
    // TODO: Generate swap summary
    return "keks";
}

std::string WildBattle::generateBattleSummary() {
    std::stringstream ret;
    ret << this->player1->Name << "'s " << this->player1->Team.at(0)->Nickname
        << " Health: " << this->player1->Team.at(0)->Health;
    ret << std::endl;
    ret << "Wild " << this->com->pokemon->Nickname
        << "'s Health: " << this->com->pokemon->Health;

    return ret.str();
}