#include "pokemon/bot/events/battle.h"

#include <string>                       // for allocator, stoi
#include <unordered_map>                // for unordered_map

#include "pokemon/battle/baseBattle.h"  // for BaseBattle
#include "pokemon/battle/battle.h"      // for isBattleActive, allBattles
#include "pokemon/global.h"             // for BotArgs
#include "pokemon/user/player.h"        // for INVALID_ID, UID
#include "tgbot/Api.h"                  // for Api
#include "tgbot/Bot.h"                  // for Bot

void moveCallback(TgBot::Bot &bot, BotArgs args) {
    if (args.size() > 2) {
        UID uid = std::stoi(args.get("queryFromID", "-1"));
        int moveIndex = std::stoi(args.get("move", "-1"));
        if (std::stoi(args.get("queryFromID")) != uid) {
            bot.getApi().answerCallbackQuery(args.get("queryID"), "Message wasn't meant for you :P", true);
            return;
        }
        if (isBattleActive(uid) && uid != INVALID_ID && moveIndex != -1) {
            BaseBattle *battle = allBattles[uid];
            battle->HandleBattle(uid, moveIndex, false);
        }
    }
}