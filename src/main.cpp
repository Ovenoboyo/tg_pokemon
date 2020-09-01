#include <iostream>
#include <cstdlib>
#include <tgbot/tgbot.h>
#include "bot/bot.h"
#include "bot/events/events.h"

int main(int argc, char const *argv[])
{
    char *token;
    size_t len;
    errno_t err = _dupenv_s(&token, &len, "TG_BOT_TOKEN");
    
    TgBot::Bot bot = registerBot(token);
    startCommand(&bot);
    battleCommand(&bot);
    pollBot(&bot);
}