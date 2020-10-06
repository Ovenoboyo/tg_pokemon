#include <cstdint>       // for int32_t
#include <stdexcept>     // for runtime_error
#include <unordered_map> // for unordered_map, _Map_base<>::mapped_type
#include <utility>       // for pair
#include <vector>        // for vector

#include "pokemon/battle/baseBattle.h" // for BaseBattle, ChatInfo
#include "pokemon/bot/bot.h"           // for bot
#include "pokemon/bot/events/events.h" // for deleteMessage
#include "pokemon/user/player.h"       // for UID

void BaseBattle::HandleRoundStart() { throw std::runtime_error("Not Implemented"); }

void BaseBattle::HandleRoundEnd() { throw std::runtime_error("Not Implemented"); }

void BaseBattle::UpdateKeyboard() { throw std::runtime_error("Not Implemented"); }

void BaseBattle::HandlePlayerChoice(UID uid, int index, bool swap) { throw std::runtime_error("Not Implemented"); }

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
    this->HandleRoundStart();
}

void BaseBattle::HandleBattleInit() {
    this->HandleRoundStart();
}