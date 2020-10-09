#include <ext/alloc_traits.h>                  // for __alloc_traits<>::value_type
#include <fmt/core.h>                          // for format
#include <memory>                              // for __shared_ptr_access, shared_ptr, allocator_traits<>::value_type
#include <string>                              // for string, allocator
#include <unordered_map>                       // for unordered_map
#include <utility>                             // for pair
#include <vector>                              // for vector

#include "pokemon/battle/baseBattle.h"         // for BaseBattle
#include "pokemon/moves.h"                     // for Move
#include "pokemon/pokemon.h"                   // for Pokemon
#include "pokemon/user/player.h"               // for Player, Player::Ptr, UID
#include "tgbot/types/InlineKeyboardButton.h"  // for InlineKeyboardButton::Ptr, InlineKeyboardButton

TgBot::InlineKeyboardButton::Ptr makeButton(std::string text, std::string data) {
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->callbackData = data;
    button->text = text;
    return button;
}

std::vector<TgBot::InlineKeyboardButton::Ptr> BaseBattle::GenerateMoveSummary(Player player) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;
    auto moveset = player.Team.at(0)->Moveset;
    int i = 0;
    for (auto m : moveset) {
        row.push_back(makeButton(m->GetName(), fmt::format("type={},move={},for={}", "moveCallback", i, player.Uid)));
        i++;
    }
    return row;
}

std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> BaseBattle::GenerateSwapReport(UID uid) {
    std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> rowHolder;
    Player::Ptr player = GetPlayer(uid);

    int i = 0, j = -1;
    for (auto p : player->Team) {
        if (i % 3 == 0) {
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;
            rowHolder.push_back(row);
            j++;
        }
        rowHolder.at(j).push_back(makeButton(p->Nickname, fmt::format("type={},for={}", "swapPokemonCallback", uid)));
        i++;
    }
    rowHolder.at(j).push_back(makeButton("<", fmt::format("type={},for={}", "swapSummaryCallback", uid)));
    return rowHolder;
}

std::string BaseBattle::GenerateBattleSummary() {
    std::string ret;
    for (auto p : this->players) {
        // TODO: Exception for wild pokemon
        ret += fmt::format("{}'s {} Health: {}\n", p.second->Name, p.second->Team.at(0)->Nickname, p.second->Team.at(0)->Health);
    }
    return ret;
}

std::vector<TgBot::InlineKeyboardButton::Ptr> BaseBattle::GenerateExtraRow(UID uid) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;
    row.push_back(makeButton("Swap Pokemon", fmt::format("type={},for={}", "swapSummaryCallback", uid)));
    return row;
}