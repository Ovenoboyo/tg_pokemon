#include <tgbot/tgbot.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "bot/events/events.h"

#include "database/dbplayer.h"
#include "player.h"
#include "pokemon.h"
#include "moves.h"
#include "battleHolder.h"
#include "global.h"

void registerStartCommand(TgBot::Bot* bot) {
    bot->getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot->getApi().sendMessage(message->chat->id, "Hi!");
    });
}

void registerBattleCommand(TgBot::Bot* bot) {
    bot->getEvents().onCommand("battle", [&bot](TgBot::Message::Ptr message) {
        auto player1 = FetchPlayer();
        auto player2 = FetchPlayer();

        BattleHolder *battle = generateBattle(player1, player2);


        if (!isBattleActive(player1->Uid) && !isBattleActive(player2->Uid)) {
            registerBattle(player1->Uid, battle);
            registerBattle(player2->Uid, battle);
        } else {
            bot->getApi().sendMessage(message->chat->id, "Player already in battle");
        }
    });
}

void registerTextCommands(TgBot::Bot* bot) {
    bot->getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        // Do something
    });
}
