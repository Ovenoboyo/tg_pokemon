#include <stdint.h> // for int32_t
#include <string>   // for string

namespace TgBot {
class Bot;
} // namespace TgBot

#ifndef EVENTS_H
#define EVENTS_H

void sendMessages(TgBot::Bot &bot, int32_t chatID, std::string message);
void registerCommands(TgBot::Bot &bot);
void handleCommands(TgBot::Bot &bot);

#endif