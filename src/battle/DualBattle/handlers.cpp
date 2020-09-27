#include <initializer_list> // for initializer_list
#include <iostream>
#include <stddef.h>      // for NULL
#include <string>        // for allocator, operator+, char_tr...
#include <unordered_map> // for unordered_map, operator!=
#include <utility>       // for swap, pair
#include <vector>        // for vector

#include "pokemon/battle/baseBattle.h" // for ChatInfo
#include "pokemon/battle/battle.h"     // for deregisterBattle
#include "pokemon/battle/dualBattle.h" // for DualBattle
#include "pokemon/bot/bot.h"           // for bot
#include "pokemon/bot/events/events.h" // for sendMessages
#include "pokemon/user/player.h"       // for UID, Player

class Move;

void DualBattle::HandleRoundStart() {
    if (!this->isEnd) {
        if (this->roundEndCounter == 0) {
            if (this->chat->isGroup) {
                sendMessages(*bot, this->chat->botReportID,
                            this->generateBattleSummary());
            }

            auto players = {this->player1, this->player2};
            for (auto p : players) {
                if (this->chat->isGroup) {
                    sendMessages(*bot, this->chat->botReportID,
                                this->generateMoveSummary(*p));
                } else {
                    sendMessages(*bot, p->Uid, this->generateBattleSummary());
                    sendMessages(*bot, p->Uid, this->generateMoveSummary(*p));
                }
            }
            this->roundEndCounter = 2;
        }
    } else {
        std::vector<UID> uidList = {this->player1->Uid, this->player2->Uid};
        deregisterBattle(this, uidList);
        return;
    }
}

void DualBattle::HandleRoundEnd() {
    bool isEnd = false;
    // TODO: Generate who played what and damage dealt summary

    auto players = {this->player1, this->player2};
    for (auto p : players) {
        if (isDefeated(p)) {
            isEnd = true;
            if (this->chat->isGroup) {
                sendMessages(*bot, this->chat->botReportID,
                             p->Name + " Lost :''(");
                break;
            }
            sendMessages(*bot, p->Uid, p->Name + " Lost :''(");
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
            sendMessages(*bot,
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
