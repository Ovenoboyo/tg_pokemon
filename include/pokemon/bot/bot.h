#include <stdlib.h> // for getenv
#include <string>   // for allocator, string

#include "tgbot/Bot.h" // for Bot

#ifndef BOT_H
#define BOT_H

inline TgBot::Bot bot(getenv("TG_BOT_TOKEN"));

void pollBot(TgBot::Bot &bot);

#endif