#ifndef EVENTS_H
#define EVENTS_H

#include <stdint.h> // for int32_t
#include <string>   // for string
#include <tgbot/tgbot.h>
#include "pokemon/user/player.h"

namespace TgBot {
class Bot;
} // namespace TgBot

void sendMessages(TgBot::Bot &bot, int32_t chatID, std::string message);
void sendMessageWKeyboard(TgBot::Bot &bot, int32_t chatIDs, std::string message, TgBot::InlineKeyboardMarkup::Ptr keyboard);
void registerCommands(TgBot::Bot &bot);
void handleCommands(TgBot::Bot &bot);

#endif