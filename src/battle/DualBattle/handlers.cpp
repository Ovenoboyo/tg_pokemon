#include <stddef.h>                     // for NULL
#include <initializer_list>             // for initializer_list
#include <memory>                       // for __shared_ptr_access, shared_ptr
#include <string>                       // for allocator, operator+, char_tr...
#include <unordered_map>                // for unordered_map, operator==
#include <utility>                      // for pair
#include <vector>                       // for vector

#include "pokemon/battle/baseBattle.h"  // for ChatInfo, isDefeated
#include "pokemon/battle/battle.h"      // for deregisterBattle
#include "pokemon/battle/dualBattle.h"  // for DualBattle
#include "pokemon/bot/bot.h"            // for bot
#include "pokemon/bot/events/events.h"  // for sendMessages
#include "pokemon/user/player.h"        // for UID, Player

class Move;

std::unordered_map<int32_t, int32_t> DualBattle::handleMessages(bool isGroup) {
    std::unordered_map<int32_t, int32_t> messageID;
    auto players = {this->player1, this->player2};
    if (isGroup) {
       messageID.insert({this->chat->botReportID, sendMessage(*bot, this->chat->botReportID, this->generateBattleSummary())});
       for (auto p : players) {
          messageID.insert({this->chat->botReportID, sendMessage(*bot, this->chat->botReportID, this->generateMoveSummary(*p))});
       }
    } else {
        for (auto p : players) {
          messageID.insert({p->Uid, sendMessage(*bot, p->Uid, this->generateMoveSummary(*p))});
       }   
    }
    return messageID;
}

std::unordered_map<int32_t, int32_t> DualBattle::HandleRoundStart() {
    if (!this->isEnd) {
        if (this->roundEndCounter == 0) {
            this->roundEndCounter = 2;
            if (this->chat->isGroup) {
                this->cleanMessages(this->chat->botReportID);
            } else {
                auto players = {this->player1, this->player2};
                for (auto p : players) {
                    this->cleanMessages(p->Uid);
                }
            }
            return this->handleMessages(this->chat->isGroup);
        }
    } else {
        std::vector<UID> uidList = {this->player1->Uid, this->player2->Uid};
        deregisterBattle(this, uidList);
    }
    return std::unordered_map<int32_t, int32_t>();
}

void DualBattle::HandleRoundEnd() {
    bool isEnd = false;
    // TODO: Generate who played what and damage dealt summary

    auto players = {this->player1, this->player2};
    for (auto p : players) {
        if (isDefeated(p)) {
            isEnd = true;
            if (this->chat->isGroup) {
                sendMessage(*bot, this->chat->botReportID,
                             p->Name + " Lost :''(");
                break;
            }
            sendMessage(*bot, p->Uid, p->Name + " Lost :''(");
        }
    }
    if (isEnd) {
        this->isEnd = true;
        return;
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

        this->roundEndCounter--;

        // Check if round ended
        if (this->roundEndCounter == 0) {
            this->ApplyMoves();
        } else {
            sendMessage(*bot,
                         (this->chat->isGroup) ? this->chat->botReportID : uid,
                         "Waiting for other player...");
        }
    } else {
        // Player already moved
    }
}

void DualBattle::SwapPokemon(UID uid, int index) {
    auto player = this->GetPlayer(uid);
    std::swap(player->Team.at(0), player->Team[index]);
}
