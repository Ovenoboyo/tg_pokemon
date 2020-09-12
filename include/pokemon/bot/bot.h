#include "string"
#include <tgbot/tgbot.h>

#ifndef BOT_H
#define BOT_H

inline TgBot::Bot bot(getenv("TG_BOT_TOKEN"));

void pollBot(TgBot::Bot &bot);

#endif