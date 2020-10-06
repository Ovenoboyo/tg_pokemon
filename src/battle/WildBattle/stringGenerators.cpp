#ifndef D0CEA30B_DBA5_4DCD_AD0C_E47996A4B82E
#define D0CEA30B_DBA5_4DCD_AD0C_E47996A4B82E
#include <ext/alloc_traits.h> // for __alloc_traits<>::value_type
#include <memory>             // for __shared_ptr_access, shared_ptr, allocator
#include <sstream>            // for operator<<, basic_ostream, basic_ostream::operator<<, stringstream
#include <string>             // for operator<<, char_traits, string
#include <vector>             // for vector

#include "fmt/core.h"                         // for format
#include "pokemon/battle/wildBattle.h"        // for WildBattle
#include "pokemon/moves.h"                    // for Move
#include "pokemon/pokemon.h"                  // for Pokemon
#include "pokemon/user/player.h"              // for Player
#include "pokemon/user/wild.h"                // for Wild
#include "tgbot/types/InlineKeyboardButton.h" // for InlineKeyboardButton::Ptr, InlineKeyboardButton

std::vector<TgBot::InlineKeyboardButton::Ptr> WildBattle::generateMoveSummary(Player player) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;
    auto moveset = player.Team.at(0)->Moveset;
    int i = 0;
    for (auto m : moveset) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->callbackData = fmt::format("type={},move={},for={}", "moveCallback", i, player.Uid);
        button->text = m->GetName();
        row.push_back(button);
        i++;
    }
    return row;
}

std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> WildBattle::GenerateSwapReport() {
    std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> rowHolder;
    int i = 0, j = -1;
    for (auto p : this->player1->Team) {
        if (i % 3 == 0) {
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;
            rowHolder.push_back(row);
            j++;
        }
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->callbackData = fmt::format("type={},for={}", "swapPokemonCallback", this->player1->Uid);
        button->text = p->Nickname;
        rowHolder.at(j).push_back(button);
        i++;
    }

    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->callbackData = fmt::format("type={},for={}", "swapSummaryCallback", this->player1->Uid);
    button->text = "<";
    rowHolder.at(j).push_back(button);
    return rowHolder;
}

std::string WildBattle::generateBattleSummary() {
    std::stringstream ret;
    ret << this->player1->Name << "'s " << this->player1->Team.at(0)->Nickname
        << " Health: " << this->player1->Team.at(0)->Health;
    ret << std::endl;
    ret << "Wild " << this->com->pokemon->Nickname << "'s Health: " << this->com->pokemon->Health;

    return ret.str();
}
#endif // D0CEA30B_DBA5_4DCD_AD0C_E47996A4B82E
