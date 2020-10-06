#include <cstdint>          // for int32_t
#include <initializer_list> // for initializer_list
#include <memory>           // for allocator, __shared_ptr_access, shared_ptr, swap
#include <stddef.h>         // for NULL
#include <string>           // for operator+, char_traits, basic_string
#include <unordered_map>    // for unordered_map, operator==, unordered_map<>::iterator, _Node_iterator...
#include <utility>          // for pair
#include <vector>           // for vector
#include <fmt/core.h>
#include <iostream>

#include "pokemon/battle/baseBattle.h"        // for ChatInfo, isDefeated
#include "pokemon/battle/battle.h"            // for deregisterBattle
#include "pokemon/battle/dualBattle.h"        // for DualBattle
#include "pokemon/bot/bot.h"                  // for bot
#include "pokemon/bot/events/events.h"        // for sendMessage, sendMessageWKeyboard
#include "pokemon/user/player.h"              // for UID, Player
#include "tgbot/types/InlineKeyboardButton.h" // for InlineKeyboardButton::Ptr
#include "tgbot/types/InlineKeyboardMarkup.h" // for InlineKeyboardMarkup, InlineKeyboardMarkup::Ptr

class Move;

std::vector<TgBot::InlineKeyboardButton::Ptr> generatePlaceholderRow(Player player) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->callbackData = "placeholder";
    button->text = player.Name;
    row.push_back(button);
    return row;
}

std::vector<TgBot::InlineKeyboardButton::Ptr> DualBattle::generateExtraRow(Player player) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;
    TgBot::InlineKeyboardButton::Ptr swapButton(new TgBot::InlineKeyboardButton);
    swapButton->callbackData = fmt::format("type={},for={}", "swapSummaryCallback", player.Uid);
    swapButton->text = "Swap Pokemon";
    row.push_back(swapButton);
    return row;
}

void DualBattle::UpdateKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    auto players = {this->player1, this->player2};
    for (auto p : players) {
        if (!p->hasPlayed) {
            keyboard->inlineKeyboard.push_back(generatePlaceholderRow(*p));
            if (this->chat->showSwapMessage.find(p->Uid) != this->chat->showSwapMessage.end() && this->chat->showSwapMessage[p->Uid]) {
                for (auto k : this->GenerateSwapReport(p->Uid)) {
                    keyboard->inlineKeyboard.push_back(k);
                }
                continue;
            }
            keyboard->inlineKeyboard.push_back(this->generateMoveSummary(*p));
            keyboard->inlineKeyboard.push_back(this->generateExtraRow(*p));

            if (!this->chat->isGroup) {
                editInlineKeyboard(*bot, p->Uid, this->chat->battleMessage[p->Uid], keyboard);
                keyboard->inlineKeyboard.clear();
            }
        }
    }  
    if (this->chat->isGroup) {
        editInlineKeyboard(*bot, this->chat->botReportID, this->chat->battleMessage[this->chat->botReportID], keyboard);
    } 
}

void DualBattle::handleMessages() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    auto players = {this->player1, this->player2};
    for (auto p : players) {
        keyboard->inlineKeyboard.push_back(generatePlaceholderRow(*p));
        keyboard->inlineKeyboard.push_back(this->generateMoveSummary(*p));
        keyboard->inlineKeyboard.push_back(generateExtraRow(*p));
        if (!this->chat->isGroup) {
            auto messageID = sendMessageWKeyboard(*bot, p->Uid, this->generateBattleSummary(), keyboard);
            this->chat->prevMessages[p->Uid].push_back(messageID);
            this->chat->battleMessage[p->Uid] = messageID;
            keyboard->inlineKeyboard.clear();
        }
    }
    if (this->chat->isGroup) {
        auto messageID = sendMessageWKeyboard(*bot, this->chat->botReportID, this->generateBattleSummary(), keyboard);
        this->chat->prevMessages[this->chat->botReportID].push_back(messageID);
        this->chat->battleMessage[this->chat->botReportID] = messageID;
    }
}

void DualBattle::HandleRoundStart() {
    if (!this->isEnd) {
        if (this->isRoundEnd()) {
            this->resetPlayerPlayed();
            if (this->chat->isGroup) {
                this->cleanMessages(this->chat->botReportID);
            } else {
                auto players = {this->player1, this->player2};
                for (auto p : players) {
                    this->cleanMessages(p->Uid);
                }
            }
            this->handleMessages();
            return;
        }
    } else {
        std::vector<UID> uidList = {this->player1->Uid, this->player2->Uid};
        deregisterBattle(this, uidList);
    }
}

void DualBattle::HandleRoundEnd() {
    bool isEnd = false;
    // TODO: Generate who played what and damage dealt summary

    auto players = {this->player1, this->player2};
    for (auto p : players) {
        if (isDefeated(p)) {
            this->isEnd = true;
            if (this->chat->isGroup) {
                sendMessage(*bot, this->chat->botReportID, p->Name + " Lost :''(");
                break;
            }
            sendMessage(*bot, p->Uid, p->Name + " Lost :''(");
        }
    }
}

bool DualBattle::isRoundEnd() {
    return (this->player1->hasPlayed && this->player2->hasPlayed);
}

void DualBattle::resetPlayerPlayed() {
    this->player1->hasPlayed = false;
    this->player2->hasPlayed = false;
}

void DualBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    if (this->playedMove.find(uid) == this->playedMove.end()) {
        auto player = this->GetPlayer(uid);

        // Check if user is swapping or playing a move
        if (swap || player->isSwapping) {
            this->SwapPokemon(uid, index);
            player->isSwapping = false;

            // Make getMoveFromIndex return empty move
            this->playedMove.insert(std::pair<UID, Move *>(uid, getMoveFromIndex(*player, 69)));
        } else {
            auto move = getMoveFromIndex(*player, index);
            if (move != NULL) {
                this->playedMove.insert(std::pair<UID, Move *>(uid, move));
            } else {
                // Can't play this move
                return;
            }
        }
        this->GetPlayer(uid)->hasPlayed = true;
        this->UpdateKeyboard();
        // Check if round ended
        if (this->isRoundEnd()) {
            this->ApplyMoves();
        } else {
            auto chatID = (this->chat->isGroup) ? this->chat->botReportID : uid;
            this->chat->prevMessages[chatID].push_back(sendMessage(*bot, chatID, "Waiting for other player..."));
        }
    } else {
        // Player already moved
    }
}

void DualBattle::SwapPokemon(UID uid, int index) {
    auto player = this->GetPlayer(uid);
    std::swap(player->Team.at(0), player->Team[index]);
}
