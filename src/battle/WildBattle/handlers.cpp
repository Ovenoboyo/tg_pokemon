#include <stddef.h>                            // for NULL
#include <cstdint>                             // for int32_t
#include <memory>                              // for __shared_ptr_access, shared_ptr, allocator
#include <string>                              // for operator+, char_traits, basic_string
#include <unordered_map>                       // for unordered_map, unordered_map<>::iterator, operator!=, operator==
#include <utility>                             // for pair
#include <vector>                              // for vector

#include "pokemon/battle/baseBattle.h"         // for ChatInfo, isDefeated
#include "pokemon/battle/battle.h"             // for deregisterBattle
#include "pokemon/battle/wildBattle.h"         // for WildBattle
#include "pokemon/bot/bot.h"                   // for bot
#include "pokemon/bot/events/events.h"         // for sendMessage, editInlineKeyboard, sendMessageWKeyboard
#include "pokemon/user/player.h"               // for UID, Player, BOT_ID, Player::Ptr
#include "tgbot/types/InlineKeyboardButton.h"  // for InlineKeyboardButton::Ptr
#include "tgbot/types/InlineKeyboardMarkup.h"  // for InlineKeyboardMarkup, InlineKeyboardMarkup::Ptr

class Move;

void WildBattle::handleMessages(int32_t chatID) {
    auto player = this->GetOtherPlayer(BOT_ID);
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    keyboard->inlineKeyboard.push_back(this->GenerateMoveSummary(*(player)));
    keyboard->inlineKeyboard.push_back(this->GenerateExtraRow(player->Uid));
    auto messageID = sendMessageWKeyboard(*bot, chatID, this->GenerateBattleSummary(), keyboard);
    this->chat->prevMessages[chatID].push_back(messageID);
    this->chat->battleMessage[chatID] = messageID;
    return;
}

void WildBattle::HandleRoundStart() {
    UID uid = this->GetOtherPlayer(BOT_ID)->Uid;
    if (!this->isEnd) {
        auto reportID = (this->chat->isGroup) ? this->chat->botReportID : uid;
        this->cleanMessages(reportID);
        this->handleMessages(reportID);
        return;
    } else {
        std::vector<UID> uidList = {uid};
        deregisterBattle(this, uidList);
    }
}

void WildBattle::UpdateKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    auto player = this->GetOtherPlayer(BOT_ID);
    if (this->chat->showSwapMessage.find(player->Uid) != this->chat->showSwapMessage.end() && this->chat->showSwapMessage[player->Uid]) {
        for (auto k : this->GenerateSwapReport(player->Uid)) {
            keyboard->inlineKeyboard.push_back(k);
        }
    } else {
        keyboard->inlineKeyboard.push_back(this->GenerateMoveSummary(*player));
        keyboard->inlineKeyboard.push_back(this->GenerateExtraRow(player->Uid));
    }

    auto reportID = (this->chat->isGroup) ? this->chat->botReportID : player->Uid;
    editInlineKeyboard(*bot, reportID, this->chat->battleMessage[reportID], keyboard);
}

void WildBattle::HandleRoundEnd() {
    bool isEnd = false;
    // TODO: Generate who played what and damage dealt summary
    for (auto p : this->players) {
        if (isDefeated(p.second)) {
            this->isEnd = true;
            if (this->chat->isGroup) {
                sendMessage(*bot, this->chat->botReportID, p.second->Name + " Lost :''(");
                break;
            }
            sendMessage(*bot, p.first, p.second->Name + " Lost :''(");
        } else if (p.second->isSwapping) {
            this->sendSwapReport(p.first);
        }
    }
}

void WildBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    if (this->playedMove.find(uid) == this->playedMove.end()) {
        auto player = this->GetOtherPlayer(BOT_ID);

        // Check if user is swapping or playing a move
        if (swap || player->isSwapping) {
            this->SwapPokemon(uid, index);
            player->isSwapping = false;

            // Make getMoveFromIndex return empty move
            this->playedMove.insert(std::pair<UID, Move *>(uid, this->GetMoveFromIndex(*player, 69)));
        } else {
            auto move = this->GetMoveFromIndex(*player, index);
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