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

void registerStartCommand(TgBot::Bot &bot) {
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
}

void registerBattleCommand(TgBot::Bot &bot) {
    bot.getEvents().onCommand("battle", [&bot](TgBot::Message::Ptr message) {
        auto player1 = FetchPlayer(boost::lexical_cast<std::string>(message->from->id));
        auto player2 = FetchPlayer("2");

        std::list<int32_t> chatIDs;
        chatIDs.push_back(message->chat->id);

        BattleHolder *battle = generateBattle(player1, player2, chatIDs);

        if (!isBattleActive(player1->Uid) && !isBattleActive(player2->Uid)) {
            registerBattle(player1->Uid, battle);
            registerBattle(player2->Uid, battle);

            std::cout << battle->Players[player1->Uid]->Team[0]->Nickname << std::endl;

            bot.getApi().sendMessage(message->chat->id, battle->generateBattleSummary());
            bot.getApi().sendMessage(message->chat->id, "player 1" + battle->generateMoveSummary(player1->Uid));
            bot.getApi().sendMessage(message->chat->id, "player 2" + battle->generateMoveSummary(player2->Uid));

        } else {
            bot.getApi().sendMessage(message->chat->id, "Player already in battle");
        }
    });
}

void sendBattleReport(TgBot::Bot &bot, int32_t chatid, BattleHolder battle) {
    bot.getApi().sendMessage(chatid, battle.generateBattleSummary());
}

void registerTextCommands(TgBot::Bot &bot) {
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (message->text.compare("attack") == 0) {
            UID uid = boost::lexical_cast<std::string>(message->from->id);
            //auto battle = allBattles[uid];
            std::map<UID, BattleHolder*>::iterator it = allBattles.find(uid);
            if(it != allBattles.end()) {
                auto battle = it->second;

                battle->HandlePlayerChoice(uid, 1);
                battle->HandlePlayerChoice("2", 1);
            }
        }
    });
}
