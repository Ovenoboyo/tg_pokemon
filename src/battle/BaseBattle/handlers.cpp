#include <stdexcept>                    // for runtime_error

#include "pokemon/battle/baseBattle.h"  // for BaseBattle
#include "pokemon/user/player.h"        // for UID
#include "pokemon/bot/bot.h"
#include "pokemon/bot/events/events.h" 

std::unordered_map<int32_t, int32_t> BaseBattle::HandleRoundStart() {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::HandleRoundEnd() {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::HandlePlayerChoice(UID uid, int index, bool swap) {
    throw std::runtime_error("Not Implemented");
}

void BaseBattle::cleanMessages(UID chatID) {
    for (auto m : this->chat->prevMessages) {
        for (auto i : m.second) {
            deleteMessage(*bot, m.first, i);
        }
    }
    this->chat->prevMessages.clear();
}

void BaseBattle::HandleBattle(UID uid, int moveNo, bool swap) {
    this->HandlePlayerChoice(uid, moveNo, swap);
    this->HandleRoundEnd();
    for (auto i : this->HandleRoundStart()) {
        this->chat->prevMessages[i.first].push_back(i.second);
    }
}

void BaseBattle::HandleBattleInit() {
    for (auto i : this->HandleRoundStart()) {
        this->chat->prevMessages[i.first].push_back(i.second);
    }
}