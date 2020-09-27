#include "pokemon/battle/wildBattle.h"

#include "pokemon/battle/battle.h"
#include "pokemon/database/conn.h"
#include "pokemon/user/player.h"
#include <memory>
#include <tgbot/tgbot.h>

WildBattle *GetWildBattle(std::shared_ptr<Player> p,
                          TgBot::Message::Ptr message) {
    WildBattle *battle;

    if (message->chat->type == TgBot::Chat::Type::Group) {
        battle = new WildBattle(p, message->chat->id);
    } else {
        battle = new WildBattle(p, INVALID_ID);
    }
    return battle;
}

std::shared_ptr<Player> GetPlayerFromID(int32_t id) {
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
            bot.getApi().sendMessage(message->chat->id,
                                     "You haven't registered yet");
            return;
        }

        auto battle = GetWildBattle(player1, message);

        registerBattle(player1->Uid, battle);
        battle->HandleRoundStart();
    }
}