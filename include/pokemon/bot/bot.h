#ifndef BOT_H
#define BOT_H

namespace TgBot {
class Bot;
} // namespace TgBot

inline TgBot::Bot *bot;

void pollBot(TgBot::Bot &bot);

#endif