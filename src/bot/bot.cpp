#include "pokemon/bot/bot.h"
#include <cstdio>
#include <string>
#include <tgbot/tgbot.h>

void pollBot(TgBot::Bot &bot) {
  try {
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
      printf("Long poll started\n");
      longPoll.start();
    }
  } catch (TgBot::TgException &e) {
    printf("error: %s\n", e.what());
  }
}