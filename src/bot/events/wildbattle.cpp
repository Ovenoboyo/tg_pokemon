#include <bits/exception.h> // for exception
#include <iostream>         // for operator<<, cout, ostream
#include <memory>           // for __shared_ptr_access, shared_ptr
#include <stdint.h>         // for int32_t

#include "pokemon/battle/battle.h"     // for isBattleActive, registerBattle
#include "pokemon/battle/wildBattle.h" // for WildBattle
#include "pokemon/database/conn.h"     // for PGConn, dbConn
#include "pokemon/user/player.h"       // for Player, INVALID_ID
#include "tgbot/Api.h"                 // for Api
#include "tgbot/Bot.h"                 // for Bot
#include "tgbot/types/Chat.h"          // for Chat, Chat::Ptr, Chat::Type
#include "tgbot/types/Message.h"       // for Message, Message::Ptr
#include "tgbot/types/User.h"          // for User, User::Ptr

WildBattle *GetWildBattle(Player::Ptr p, TgBot::Message::Ptr message) {
    WildBattle *battle;
    auto wild = std::make_shared<Player>(true);
    if (message->chat->type == TgBot::Chat::Type::Group) {
        battle = new WildBattle({p, wild}, message->chat->id);
    } else {
        battle = new WildBattle({p, wild}, INVALID_ID);
    }
    return battle;
}

Player::Ptr GetPlayerFromID(int32_t id) {
    try {
        return dbConn->FetchPlayer(id);
    } catch (const std::exception &e) {
        std::cout << e.what();
        return std::make_shared<Player>();
    }
}

void validateWildBattle(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    if (!isBattleActive(message->from->id)) {
        auto player1 = GetPlayerFromID(message->from->id);
        if (player1->isEmpty) {
            bot.getApi().sendMessage(message->chat->id, "You haven't registered yet");
            return;
        }

        auto battle = GetWildBattle(player1, message);

        registerBattle(player1->Uid, battle);
        battle->HandleBattleInit();
    }
}