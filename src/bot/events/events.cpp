#include "pokemon/bot/events/events.h"

#include <algorithm>                            // for max
#include <bits/exception.h>                     // for exception
#include <boost/algorithm/string/case_conv.hpp> // for to_lower
#include <boost/algorithm/string/trim.hpp>      // for trim
#include <cstdint>                              // for int32_t
#include <iostream>                             // for operator<<, cout
#include <memory>                               // for __shared_ptr_access
#include <string>                               // for allocator, string
#include <unordered_map>                        // for unordered_map, opera...
#include <utility>                              // for pair
#include <vector>                               // for vector

#include "pokemon/battle/baseBattle.h"        // for BaseBattle, INVALID_ID
#include "pokemon/battle/battle.h"            // for isBattleActive, regi...
#include "pokemon/battle/dualBattle.h"        // for DualBattle
#include "pokemon/bot/events/battleRequest.h" // for allRequests
#include "pokemon/database/dbplayer.h"        // for FetchPlayer, isPlaye...
#include "pokemon/user/player.h"              // for Player, UID
#include "tgbot/Api.h"                        // for Api
#include "tgbot/Bot.h"                        // for Bot
#include "tgbot/EventBroadcaster.h"           // for EventBroadcaster
#include "tgbot/tools/StringTools.h"          // for startsWith
#include "tgbot/types/BotCommand.h"           // for BotCommand::Ptr, Bot...
#include "tgbot/types/Chat.h"                 // for Chat, Chat::Ptr, Cha...
#include "tgbot/types/Message.h"              // for Message, Message::Ptr
#include "tgbot/types/User.h"                 // for User, User::Ptr

void StartCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
}

void validateAndStartBattle(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    auto it = allRequests.find(message->from->id);
    if (it != allRequests.end()) {
        if (!isBattleActive(message->from->id) &&
            !isBattleActive(allRequests[message->from->id])) {
            Player *player1, *player2;
            try {
                player1 = FetchPlayer(allRequests[message->from->id]);
                player2 = FetchPlayer(message->from->id);
            } catch (const std::exception &e) {
                std::cout << e.what();
                bot.getApi().sendMessage(message->chat->id, e.what());
                return;
            }

            BaseBattle *battle;

            if (message->chat->type == TgBot::Chat::Type::Group) {
                battle = new DualBattle(player1, player2, message->chat->id);
            } else {
                battle = new DualBattle(player1, player2, INVALID_ID);
            }

            registerBattle(player1->Uid, battle);
            registerBattle(player2->Uid, battle);
            battle->HandleBattle();
        } else {
            bot.getApi().sendMessage(message->chat->id,
                                     "Player already in battle");
        }
    }
}

void AskBattleCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    std::string requestedUsername = message->text.substr(7);

    boost::algorithm::trim(requestedUsername);
    if (StringTools::startsWith(requestedUsername, "@")) {
        // Removes @
        requestedUsername.erase(0, 1);
    }

    int32_t requesterID = message->from->id;
    int32_t requestedID = isPlayerRegistered(requestedUsername);

    if (requestedID != INVALID_ID) {
        allRequests.insert(
            std::pair<int32_t, int32_t>(requestedID, requesterID));
        bot.getApi().sendMessage(message->chat->id, "@" + requestedUsername +
                                                        " Type yes to accept");
    } else {
        bot.getApi().sendMessage(message->chat->id, "No such user");
    }
}

void sendMessages(TgBot::Bot &bot, int32_t chatIDs, std::string message) {
    bot.getApi().sendMessage(chatIDs, message);
}

void handlePlayerAttack(TgBot::Message::Ptr message) {
    if (allBattles.find(message->from->id) != allBattles.end()) {
        auto battle = allBattles[message->from->id];

        battle->HandleBattle(message->from->id, 1, false);
    }
}

void registerCommands(TgBot::Bot &bot) {
    std::vector<TgBot::BotCommand::Ptr> commands;
    TgBot::BotCommand::Ptr cmdArray(new TgBot::BotCommand);

    cmdArray->command = "battle";
    cmdArray->description = "Initiate a battle";
    commands.push_back(cmdArray);

    bot.getApi().setMyCommands(commands);
}

void handleCommands(TgBot::Bot &bot) {
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            StartCommand(bot, message);
        } else if (StringTools::startsWith(message->text, "/battle")) {
            AskBattleCommand(bot, message);
        } else if (message->text == "yes") {
            validateAndStartBattle(bot, message);
        } else if (message->text == "attack") {
            handlePlayerAttack(message);
        }
    });
}
