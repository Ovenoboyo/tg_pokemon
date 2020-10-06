#include <ext/alloc_traits.h> // for __alloc_traits<>::value_type
#include <memory>             // for __shared_ptr_access, shared_ptr, allocator
#include <sstream>            // for operator<<, basic_ostream, basic_ostream::operator<<, stringstream
#include <string>             // for operator<<, char_traits, string
#include <vector>             // for vector
#include <iostream>

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
        button->callbackData = fmt::format("type={},move={},for={}", "moveCallback", i, player.Uid);
        button->text = m->GetName();
        row.push_back(button);
        i++;
    }
    return row;
}

std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> DualBattle::GenerateSwapReport(UID uid) {
    std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> rowHolder;
    Player::Ptr player;
    if (this->player1->Uid == uid) {
        player = this->player1;
    } else if (this->player2->Uid == uid) {
        player = this->player2;
    } else {
        // TODO: Throw an exception here
    }

    std::string ret = "";
    int i = 0, j = -1;
    for (auto p : player->Team) {
        if (i % 3 == 0) {
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;
            rowHolder.push_back(row);
            j++;
        }
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->callbackData = fmt::format("type={},for={}", "swapPokemonCallback", uid);
        button->text = p->Nickname;
        rowHolder.at(j).push_back(button);
        i++;
    }

    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->callbackData = fmt::format("type={},for={}", "swapSummaryCallback", uid);
    std::cout << uid << std::endl;
    button->text = "<";
    rowHolder.at(j).push_back(button);
    return rowHolder;
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