#ifndef EVENTS_H
#define EVENTS_H

#include <stdint.h> // for int32_t
#include <string>   // for string

#include "tgbot/types/InlineKeyboardMarkup.h" // for InlineKeyboardMarkup

namespace TgBot {
class Bot;
} // namespace TgBot

int32_t sendMessage(TgBot::Bot &bot, int32_t chatID, std::string message);
int32_t sendMessageWKeyboard(TgBot::Bot &bot, int32_t chatIDs, std::string message,
                             TgBot::InlineKeyboardMarkup::Ptr keyboard);
void editInlineKeyboard(TgBot::Bot &bot, int32_t chatID, int32_t messageID, TgBot::InlineKeyboardMarkup::Ptr keyboard);
void deleteMessage(TgBot::Bot &bot, int32_t chatIDs, int32_t messageID);
void registerCommands(TgBot::Bot &bot);
void handleCommands(TgBot::Bot &bot);
void handleCallbacks(TgBot::Bot &bot);

#endif