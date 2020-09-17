#include <initializer_list> // for initializer_list
#include <stddef.h>         // for NULL
#include <string>           // for allocator, operator+, char_tr...
#include <unordered_map>    // for unordered_map, operator!=
#include <utility>          // for swap, pair
#include <vector>           // for vector

#include "pokemon/battle/baseBattle.h" // for ChatInfo
#include "pokemon/battle/battle.h"     // for deregisterBattle
#include "pokemon/battle/wildBattle.h" // for DualBattle
#include "pokemon/bot/bot.h"           // for bot
#include "pokemon/bot/events/events.h" // for sendMessages
#include "pokemon/user/player.h"            // for UID, Player

class Move;

void WildBattle::HandleRoundStart() {
    if (this->chat->isGroup) {
        sendMessages(*bot, this->chat->botReportID,
                     this->generateBattleSummary());
        sendMessages(*bot, this->chat->botReportID,
                        this->generateMoveSummary(*(this->player1)));
    } else {
        sendMessages(*bot, this->player1->Uid, this->generateBattleSummary());
        sendMessages(*bot, this->player1->Uid, this->generateMoveSummary(*(this->player1)));
    }
}

void WildBattle::HandleRoundEnd() {
    bool isEnd = false;
    // TODO: Generate who played what and damage dealt summary

    if (isDefeated(this->player1)) {
        isEnd = true;
        if (this->chat->isGroup) {
            sendMessages(*bot, this->chat->botReportID,
                            this->player1->Name + " Lost :''(");
        }
        sendMessages(*bot, this->player1->Uid, this->player1->Name + " Lost :''(");
    } else if (isDefeated(this->com)) {
        isEnd = true;
        if (this->chat->isGroup) {
            sendMessages(*bot, this->chat->botReportID,
                        "Wild "+ this->com->pokemon->Nickname +"Lost :''(");
        }
        sendMessages(*bot, this->player1->Uid, this->player1->Name + " Lost :''(");
    }

    if (isEnd) {
        std::vector<UID> uidList = {this->player1->Uid};
        deregisterBattle(this, uidList);
        return;
    }
}

void WildBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    if (this->playedMove.find(uid) != this->playedMove.end()) {
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

        //TODO: bot plays move here
        this->ApplyMoves();
    } else {
        // Player already moved
    }
}

void WildBattle::SwapPokemon(UID uid, int index) {
    auto player = this->player1;
    std::swap(player->Team.at(0), player->Team[index]);
}

bool WildBattle::isDefeated(Wild *com) {
    if (com->pokemon->Health <= 0) {
        return true;
    }
    return false;
}

bool WildBattle::isDefeated(Player *player) {
    return isDefeated(player);
}    
