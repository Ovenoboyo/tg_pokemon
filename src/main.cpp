#include <iostream>
#include <cstdlib>
#include <tgbot/tgbot.h>
#include "bot/bot.h"
#include "bot/events/events.h"
#include <boost/asio.hpp>

int main(int argc, char const *argv[], char *envp[])
{
    // char *token;
    // token = getenv("TG_BOT_TOKEN");

    std::cout << "hello";
    
    TgBot::Bot bot = registerBot("1323692220:AAGvJ-9Etm-G-oapvjnmYxRgLbBHIy7ddUo");
    registerStartCommand(&bot);
    registerBattleCommand(&bot);
    registerTextCommands(&bot);
    pollBot(&bot);
}