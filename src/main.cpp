#include "bot/bot.h"
#include "bot/events/events.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <tgbot/tgbot.h>

int main(int argc, char const *argv[], char *envp[]) {
  char *token;
  token = getenv("TG_BOT_TOKEN");

  TgBot::Bot bot = registerBot(token);

  registerStartCommand(bot);
  registerBattleCommand(bot);
  registerTextCommands(bot);
  pollBot(bot);
}