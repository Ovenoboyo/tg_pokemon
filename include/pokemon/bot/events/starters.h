#ifndef D10D1D0E_9D92_4399_A5C6_71A188691675
#define D10D1D0E_9D92_4399_A5C6_71A188691675

#include <tgbot/tgbot.h>
#include <pokemon/user/player.h>

inline std::unordered_map<UID, int32_t> starterMessages;

void sendStarterMessage(TgBot::Bot &bot, int32_t chatID, UID uid);
void handleStarterCallback(TgBot::Bot &bot);
void pickStarter(TgBot::Bot &bot, TgBot::Message::Ptr message);

#endif /* D10D1D0E_9D92_4399_A5C6_71A188691675 */
