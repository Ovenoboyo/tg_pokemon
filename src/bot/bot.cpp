#include "pokemon/bot/bot.h"

#include <cstdio> // for printf
#include <memory> // for __shared_ptr_access
#include <string> // for string

#include "tgbot/Api.h"            // for Api
#include "tgbot/TgException.h"    // for TgException
#include "tgbot/net/TgLongPoll.h" // for TgLongPoll
#include "tgbot/types/User.h"     // for User, User::Ptr

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