#include <tgbot/tgbot.h>

#ifndef EVENTS_H
#define EVENTS_H

void registerStartCommand(TgBot::Bot* bot);
void registerBattleCommand(TgBot::Bot* bot);
void registerTextCommands(TgBot::Bot* bot);

#endif