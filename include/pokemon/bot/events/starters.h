#ifndef D10D1D0E_9D92_4399_A5C6_71A188691675
#define D10D1D0E_9D92_4399_A5C6_71A188691675

#include <pokemon/user/player.h>  // for UID
#include <stdint.h>               // for int32_t
#include <unordered_map>          // for unordered_map

#include "tgbot/types/Message.h"  // for Message, Message::Ptr

class BotArgs;

namespace TgBot {
class Bot;
}  // namespace TgBot

inline std::unordered_map<UID, int32_t> starterMessages;

void sendStarterMessage(TgBot::Bot &bot, int32_t chatID, UID uid);
void starterCallback(TgBot::Bot &bot, BotArgs args);
void pickStarter(TgBot::Bot &bot, TgBot::Message::Ptr message);

#endif /* D10D1D0E_9D92_4399_A5C6_71A188691675 */
