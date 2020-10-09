#include "pokemon/bot/events/events.h"

#include <iostream>                         // for operator<<, endl, basic_ostream, cout, ostream
#include <memory>                           // for __shared_ptr_access
#include <unordered_map>                    // for unordered_map
#include <vector>                           // for vector

#include "pokemon/battle/baseBattle.h"      // for BaseBattle
#include "pokemon/battle/battle.h"          // for isBattleActive, allBattles
#include "pokemon/bot/events/battle.h"      // for moveCallback, swapSummaryCallback
#include "pokemon/bot/events/dualbattle.h"  // for AskBattleCommand, validateAndStartBattle
#include "pokemon/bot/events/starters.h"    // for pickStarter, starterCallback
#include "pokemon/bot/events/wildbattle.h"  // for validateWildBattle
#include "pokemon/database/conn.h"          // for PGConn, dbConn
#include "pokemon/global.h"                 // for BotArgs
#include "tgbot/Api.h"                      // for Api
#include "tgbot/Bot.h"                      // for Bot
#include "tgbot/EventBroadcaster.h"         // for EventBroadcaster
#include "tgbot/TgException.h"              // for TgException
#include "tgbot/tools/StringTools.h"        // for startsWith
#include "tgbot/types/BotCommand.h"         // for BotCommand::Ptr, BotCommand
#include "tgbot/types/CallbackQuery.h"      // for CallbackQuery, CallbackQuery::Ptr
#include "tgbot/types/Chat.h"               // for Chat, Chat::Ptr
#include "tgbot/types/Message.h"            // for Message, Message::Ptr
#include "tgbot/types/User.h"               // for User, User::Ptr

void StartCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) { bot.getApi().sendMessage(message->chat->id, "Hi!"); }

int32_t sendMessage(TgBot::Bot &bot, int32_t chatIDs, std::string message) {
    return bot.getApi().sendMessage(chatIDs, message)->messageId;
}

void deleteMessage(TgBot::Bot &bot, int32_t chatID, int32_t messageID) {
    bot.getApi().deleteMessage(chatID, messageID);
}

int32_t sendMessageWKeyboard(TgBot::Bot &bot, int32_t chatIDs, std::string message,
                             TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    return bot.getApi().sendMessage(chatIDs, message, true, 0, keyboard, "Markdown")->messageId;
}

void editInlineKeyboard(TgBot::Bot &bot, int32_t chatID, int32_t messageID, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    try {
        bot.getApi().editMessageReplyMarkup(chatID, messageID, "", keyboard);
    } catch (const TgBot::TgException &e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

void handlePlayerAttack(TgBot::Message::Ptr message) {
    if (isBattleActive(message->from->id)) {
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
            if (!dbConn->isPlayerRegistered(message->from->id)) {
                pickStarter(bot, message);
                return;
            } else {
                StartCommand(bot, message);
                return;
            }
        }

        if (StringTools::startsWith(message->text, "/battle")) {
            AskBattleCommand(bot, message);
        } else if (message->text.compare("yes") == 0) {
            validateAndStartBattle(bot, message);
        } else if (message->text.compare("attack") == 0) {
            handlePlayerAttack(message);
        } else if (StringTools::startsWith(message->text, "/wild")) {
            validateWildBattle(bot, message);
        }
    });
}

void handleCallbacks(TgBot::Bot &bot) {
    try {
        bot.getEvents().onCallbackQuery([&bot](TgBot::CallbackQuery::Ptr query) {
            BotArgs args;
            args.parseQueryDetails(query);
            if (args.size() > 0) {
                if (args.get("type").compare("starterCallback") == 0) {
                    starterCallback(bot, args);
                } else if (args.get("type").compare("moveCallback") == 0) {
                    moveCallback(bot, args);
                } else if (args.get("type").compare("swapSummaryCallback") == 0) {
                    swapSummaryCallback(bot, args);
                }
            }
        });
    } catch (const TgBot::TgException &e) {
        std::cout << e.what() << std::endl;
    }
}
