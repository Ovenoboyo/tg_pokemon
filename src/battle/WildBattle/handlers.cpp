#include <stddef.h>                            // for NULL
#include <cstdint>                             // for int32_t
#include <memory>                              // for allocator, shared_ptr, __shared_ptr_access, swap
#include <string>                              // for operator+, char_traits, basic_string
#include <unordered_map>                       // for unordered_map, operator==, unordered_map<>::iterator, _Node_iterator...
#include <utility>                             // for move, pair
#include <vector>                              // for vector

#include "pokemon/battle/baseBattle.h"         // for ChatInfo, isDefeated
#include "pokemon/battle/battle.h"             // for deregisterBattle
#include "pokemon/battle/wildBattle.h"         // for WildBattle
#include "pokemon/bot/bot.h"                   // for bot
#include "pokemon/bot/events/events.h"         // for sendMessage, sendMessageWKeyboard
#include "pokemon/pokemon.h"                   // for Pokemon
#include "pokemon/user/player.h"               // for UID, Player
#include "pokemon/user/wild.h"                 // for Wild
#include "tgbot/types/InlineKeyboardButton.h"  // for InlineKeyboardButton::Ptr
#include "tgbot/types/InlineKeyboardMarkup.h"  // for InlineKeyboardMarkup, InlineKeyboardMarkup::Ptr

class Move;

std::unordered_map<int32_t, int32_t> WildBattle::handleMessages(int32_t chatID) {
    std::unordered_map<int32_t, int32_t> messageID;
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    keyboard->inlineKeyboard.push_back(this->generateMoveSummary(*(this->player1)));
    messageID.insert({chatID, sendMessageWKeyboard(*bot, chatID, this->generateBattleSummary(), keyboard)});
    return std::move(messageID);
}

std::unordered_map<int32_t, int32_t> WildBattle::HandleRoundStart() {
    if (!this->isEnd) {
        auto reportID = (this->chat->isGroup) ? this->chat->botReportID : this->player1->Uid;
        this->cleanMessages(reportID);
        return std::move(this->handleMessages(reportID));
    } else {
        std::vector<UID> uidList = {this->player1->Uid};
        deregisterBattle(this, uidList);
    }
    return std::unordered_map<int32_t, int32_t>();
}

void WildBattle::HandleRoundEnd() {
    bool isEnd = false;
    // TODO: Generate who played what and damage dealt summary

    if (isDefeated(this->player1)) {
        isEnd = true;
        if (this->chat->isGroup) {
            sendMessage(*bot, this->chat->botReportID,
                         this->player1->Name + " Lost :''(");
        }
        sendMessage(*bot, this->player1->Uid,
                     this->player1->Name + " Lost :''(");
    } else if (isDefeated(this->com)) {
        isEnd = true;
        if (this->chat->isGroup) {
            sendMessage(*bot, this->chat->botReportID,
                         "Wild " + this->com->pokemon->Nickname + "Lost :''(");
        }
        sendMessage(*bot, this->player1->Uid,
                     this->player1->Name + " Lost :''(");
    }

    if (isEnd) {
        this->isEnd = true;
        return;
    }
}

void WildBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    if (this->playedMove.find(uid) == this->playedMove.end()) {
        auto player = this->player1;

        // Check if user is swapping or playing a move
        if (swap || player->isSwapping) {
            this->SwapPokemon(uid, index);
            player->isSwapping = false;

            // Make getMoveFromIndex return empty move
            this->playedMove.insert(
                std::pair<UID, Move *>(uid, getMoveFromIndex(*player, 69)));
        } else {
            auto move = getMoveFromIndex(*player, index);
            if (move != NULL) {
                this->playedMove.insert(std::pair<UID, Move *>(uid, move));
            } else {
                // Can't play this move
                return;
            }
        }

        // TODO: bot plays move here
        this->ApplyMoves();
    } else {
        // Player already moved
    }
}

void WildBattle::SwapPokemon(UID uid, int index) {
    auto player = this->player1;
    std::swap(player->Team.at(0), player->Team[index]);
}

bool WildBattle::isDefeated(std::shared_ptr<Wild> com) {
    if (com->pokemon->Health <= 0) {
        return true;
    }
    return false;
}

bool WildBattle::isDefeated(std::shared_ptr<Player> player) {
    using ::isDefeated;
    return isDefeated(player);
}
