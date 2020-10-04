#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>        // for string, allocator
#include <unordered_map> // for unordered_map

#include "tgbot/types/CallbackQuery.h" // for CallbackQuery, CallbackQuery::Ptr

enum ElementType {
    NIL,
    NORMAL,
    FIGHT,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCH,
    ICE,
    DRAGON
};

class BotArgs {
  private:
    std::unordered_map<std::string, std::string> args;

  public:
    void parseCallbackData(std::string data);
    void parseQueryDetails(TgBot::CallbackQuery::Ptr query);
    std::string get(std::string i, std::string def = "");
    int size();
};

std::string getEnvVar(std::string const &key);
#endif
