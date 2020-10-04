#include <ext/alloc_traits.h> // for __alloc_traits<>::value_type
#include <memory>             // for __shared_ptr_access, shared_ptr, allocator
#include <sstream>            // for operator<<, basic_ostream, basic_ostream::operator<<, stringstream
#include <string>             // for operator<<, char_traits, string
#include <vector>             // for vector

#include "fmt/core.h"                         // for format
#include "pokemon/battle/dualBattle.h"        // for DualBattle
#include "pokemon/moves.h"                    // for Move
#include "pokemon/pokemon.h"                  // for Pokemon
#include "pokemon/user/player.h"              // for Player
#include "tgbot/types/InlineKeyboardButton.h" // for InlineKeyboardButton::Ptr, InlineKeyboardButton

std::vector<TgBot::InlineKeyboardButton::Ptr> DualBattle::generateMoveSummary(Player player) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;
    auto moveset = player.Team.at(0)->Moveset;
    int i = 0;
    for (auto m : moveset) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->callbackData = fmt::format("type={},move={},moveFor={}", "moveCallback", i, player.Uid);
        button->text = m->GetName();
        row.push_back(button);
        i++;
    }
    return row;
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