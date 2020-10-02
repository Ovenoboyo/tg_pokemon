#include "pokemon/bot/events/battle.h"

#include "pokemon/user/player.h"
#include "pokemon/battle/battle.h"
#include "pokemon/battle/baseBattle.h"
#include "pokemon/global.h"
#include <tgbot/tgbot.h>
#include <iostream>
#include <string>

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