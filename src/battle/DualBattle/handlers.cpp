#include <stddef.h>                            // for NULL
#include <cstdint>                             // for int32_t
#include <memory>                              // for __shared_ptr_access, allocator, shared_ptr
#include <string>                              // for operator+, char_traits, basic_string, string
#include <unordered_map>                       // for unordered_map, unordered_map<>::iterator, _Map_base<>::mapped_type
#include <utility>                             // for pair
#include <vector>                              // for vector

#include "pokemon/battle/baseBattle.h"         // for ChatInfo, isDefeated
#include "pokemon/battle/battle.h"             // for deregisterBattle
#include "pokemon/battle/dualBattle.h"         // for DualBattle
#include "pokemon/bot/bot.h"                   // for bot
#include "pokemon/bot/events/events.h"         // for sendMessage, editInlineKeyboard, sendMessageWKeyboard
#include "pokemon/user/player.h"               // for UID, Player, Player::Ptr
#include "tgbot/types/InlineKeyboardButton.h"  // for InlineKeyboardButton::Ptr, InlineKeyboardButton
#include "tgbot/types/InlineKeyboardMarkup.h"  // for InlineKeyboardMarkup, InlineKeyboardMarkup::Ptr

class Move;

std::vector<TgBot::InlineKeyboardButton::Ptr> generatePlaceholderRow(Player player) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->callbackData = "placeholder";
    button->text = player.Name;
    row.push_back(button);
    return row;
}

void DualBattle::UpdateKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    for (auto p : this->players) {
        if (!p.second->hasPlayed) {
            keyboard->inlineKeyboard.push_back(generatePlaceholderRow(*p.second));
            if (this->chat->showSwapMessage.find(p.first) != this->chat->showSwapMessage.end() && this->chat->showSwapMessage[p.first]) {
                for (auto k : this->GenerateSwapReport(p.second->Uid)) {
                    keyboard->inlineKeyboard.push_back(k);
                }
                continue;
            }
            keyboard->inlineKeyboard.push_back(this->GenerateMoveSummary(*p.second));
            keyboard->inlineKeyboard.push_back(this->GenerateExtraRow(p.second->Uid));

            if (!this->chat->isGroup) {
                editInlineKeyboard(*bot, p.first, this->chat->battleMessage[p.first], keyboard);
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
    for (auto p : players) {
        keyboard->inlineKeyboard.push_back(generatePlaceholderRow(*p.second));
        keyboard->inlineKeyboard.push_back(this->GenerateMoveSummary(*p.second));
        keyboard->inlineKeyboard.push_back(this->GenerateExtraRow(p.second->Uid));
        if (!this->chat->isGroup) {
            auto messageID = sendMessageWKeyboard(*bot, p.first, this->GenerateBattleSummary(), keyboard);
            this->chat->prevMessages[p.first].push_back(messageID);
            this->chat->battleMessage[p.first] = messageID;
            keyboard->inlineKeyboard.clear();
        }
    }
    if (this->chat->isGroup) {
        auto messageID = sendMessageWKeyboard(*bot, this->chat->botReportID, this->GenerateBattleSummary(), keyboard);
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
                for (auto p : this->players) {
                    this->cleanMessages(p.first);
                }
            }
            this->handleMessages();
            return;
        }
    } else {
        std::vector<int> uidList;
        for(auto const& imap: this->players) {
            uidList.push_back(imap.first);
        }
        deregisterBattle(this, uidList);
    }
}

void DualBattle::HandleRoundEnd() {
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

bool DualBattle::isRoundEnd() {
    for (auto p : players) {
        if (!p.second->hasPlayed) {
            return false;
        }
    }
    return true;
}

void DualBattle::resetPlayerPlayed() {
    for (auto p : this->players) {
        p.second->hasPlayed = false;
    }
}

void DualBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    if (this->playedMove.find(uid) == this->playedMove.end()) {
        auto player = this->GetPlayer(uid);

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
