#include <bits/exception.h> // for exception
#include <iostream>         // for operator<<, cout, ostream
#include <memory>           // for allocator

#include "pokemon/bot/bot.h"             // for bot, pollBot
#include "pokemon/bot/events/events.h"   // for handleCommands, registerCom...
#include "pokemon/bot/events/starters.h" // for handleStarterCallback
#include "pokemon/database/conn.h"       // for PGConn, dbConn
#include "pokemon/global.h"              // for getEnvVar
#include "tgbot/Bot.h"                   // for Bot

int main(int argc, char const *argv[], char *envp[]) {
    try {
        dbConn = new PGConn();
        bot = new TgBot::Bot(getEnvVar("TG_BOT_TOKEN"));
    } catch (const std::exception &e) {
        std::cout << e.what();
        return -1;
    }

    registerCommands(*bot);
    handleCommands(*bot);
    handleCallbacks(*bot);
    pollBot(*bot);
}