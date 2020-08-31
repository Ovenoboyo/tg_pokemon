#include <iostream>
#include <cstdlib>
#include "bot/bot.h"
#include "bot/events/events.h"
#include "tgbot/tgbot.h"

int main(int argc, char const *argv[])
{
    TgBot::Bot bot = registerBot(getenv("TG_BOT_TOKEN"));
    startCommand(&bot);
    battleCommand(&bot);
    pollBot(&bot);
}