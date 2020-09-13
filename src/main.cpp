#include "pokemon/bot/bot.h"           // for bot, pollBot
#include "pokemon/bot/events/events.h" // for handleCommands, registerCommands

int main(int argc, char const *argv[], char *envp[]) {
  // registerStartCommand(bot);
  // registerBattleCommand(bot);
  // registerTextCommands(bot);
  registerCommands(bot);
  handleCommands(bot);
  pollBot(bot);
}