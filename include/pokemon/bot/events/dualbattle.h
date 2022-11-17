#ifndef C1D1E2C3_1F30_4237_988E_CE785DD4FFD3
#define C1D1E2C3_1F30_4237_988E_CE785DD4FFD3

#include <bits/exception.h>       // for exception
#include <stdint.h>               // for int32_t
#include <unordered_map>          // for unordered_map

#include "tgbot/types/Message.h"  // for Message, Message::Ptr

namespace TgBot {
class Bot;
}  // namespace TgBot

/**
 * @brief Holds pending battle requests
 *
 */
inline std::unordered_map<int32_t, int32_t> allRequests;

void RegisterRequest(int32_t p2, int32_t p1);
void DeregisterRequest(int32_t p2);
int32_t GetRequested(int32_t requester);
bool HasRequested(int32_t requester);
void AskBattleCommand(TgBot::Bot &bot, TgBot::Message::Ptr message);
void validateAndStartBattle(TgBot::Bot &bot, TgBot::Message::Ptr message);


struct InBattleException: public std::exception {
  const char * what () const throw () {
    return "Player already in battle";
  }
};

#endif /* C1D1E2C3_1F30_4237_988E_CE785DD4FFD3 */
