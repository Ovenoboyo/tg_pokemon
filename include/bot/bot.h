#include <tgbot/tgbot.h>
#include "string"

#ifndef BOT_H
#define BOT_H

TgBot::Bot registerBot(std::string token);
void pollBot(TgBot::Bot &bot);

#endif