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
        deleteMessage(*bot, m.first, m.second);
    }
    this->chat->prevMessages.clear();
}

void BaseBattle::HandleBattle(UID uid, int moveNo, bool swap) {
    this->HandlePlayerChoice(uid, moveNo, swap);
    this->HandleRoundEnd();
    auto IDs = this->HandleRoundStart();
    this->chat->prevMessages.merge(IDs);
}

void BaseBattle::HandleBattleInit() {
    auto IDs = this->HandleRoundStart();
    this->chat->prevMessages.merge(IDs);
}