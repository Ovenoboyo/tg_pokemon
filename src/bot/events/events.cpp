#include "pokemon/bot/events/events.h"
#include "pokemon/battle/battle.h"
#include "pokemon/battle/baseBattle.h"
#include "pokemon/database/conn.h"
#include "pokemon/bot/events/starters.h"
#include "pokemon/bot/events/dualbattle.h"
#include "pokemon/bot/events/wildbattle.h"

void StartCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
}

void sendMessages(TgBot::Bot &bot, int32_t chatIDs, std::string message) {
    bot.getApi().sendMessage(chatIDs, message);
}

void sendMessageWKeyboard(TgBot::Bot &bot, int32_t chatIDs, std::string message, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot.getApi().sendMessage(chatIDs, message, true, 0, keyboard, "Markdown");
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
