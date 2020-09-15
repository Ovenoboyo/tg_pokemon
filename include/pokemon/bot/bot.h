namespace TgBot {
class Bot;
} // namespace TgBot

#ifndef BOT_H
#define BOT_H

inline TgBot::Bot *bot;

void pollBot(TgBot::Bot &bot);

#endif