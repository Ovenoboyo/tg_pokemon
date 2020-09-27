#include <ext/alloc_traits.h>           // for __alloc_traits<>::value_type
#include <memory>                       // for __shared_ptr_access, shared_ptr
#include <sstream>                      // for operator<<, basic_ostream
#include <string>                       // for operator<<, string, char_traits
#include <vector>                       // for vector

#include "fmt/core.h"                   // for format
#include "pokemon/battle/wildBattle.h"  // for WildBattle
#include "pokemon/moves.h"              // for Move
#include "pokemon/pokemon.h"            // for Pokemon
#include "pokemon/user/player.h"        // for Player
#include "pokemon/user/wild.h"          // for Wild

std::string WildBattle::generateMoveSummary(Player player) {
    auto moveset = player.Team.at(0)->Moveset;
    std::string ret = "";
    int i = 0;
    for (auto m : moveset) {
        ret += fmt::format("Move {0}: {1}\n", i, m->GetName());
        i++;
    }
    return ret;
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