#include <tgbot/tgbot.h>

#ifndef EVENTS_H
#define EVENTS_H

void sendMessages(TgBot::Bot &bot, int32_t chatID, std::string message);
void registerCommands(TgBot::Bot &bot);
void handleCommands(TgBot::Bot &bot);

#endif