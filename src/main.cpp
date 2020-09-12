#include "bot/bot.h"
#include "bot/events/events.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <tgbot/tgbot.h>

int main(int argc, char const *argv[], char *envp[]) {
  // registerStartCommand(bot);
  // registerBattleCommand(bot);
  // registerTextCommands(bot);
  registerCommands(bot);
  handleCommands(bot);
  pollBot(bot);
}