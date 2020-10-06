#include "pokemon/bot/events/battle.h"

#include <iostream>
#include <string>        // for allocator, stoi
#include <unordered_map> // for unordered_map

#include "pokemon/battle/baseBattle.h" // for BaseBattle
#include "pokemon/battle/battle.h"     // for isBattleActive, allBattles
#include "pokemon/global.h"            // for BotArgs
#include "pokemon/user/player.h"       // for INVALID_ID, UID
#include "tgbot/Api.h"                 // for Api
#include "tgbot/Bot.h"                 // for Bot

void moveCallback(TgBot::Bot &bot, BotArgs args) {
    if (args.size() > 2) {
        UID uid = std::stoi(args.get("queryFromID", "-1"));
        int moveIndex = std::stoi(args.get("move", "-1"));
        std::cout << args.get("for") << std::endl;
        if (std::stoi(args.get("for", "-1")) != uid) {
            bot.getApi().answerCallbackQuery(args.get("queryID"), "Message wasn't meant for you :P", true);
            return;
        }
        if (isBattleActive(uid) && uid != INVALID_ID && moveIndex != -1) {
            BaseBattle *battle = allBattles[uid];
            battle->HandleBattle(uid, moveIndex, false);
        }
    }
}

void swapSummaryCallback(TgBot::Bot &bot, BotArgs args) {
    if (args.size() > 1) {
        UID uid = std::stoi(args.get("queryFromID", "-1"));
        if (std::stoi(args.get("for")) != uid && isBattleActive(uid)) {
            bot.getApi().answerCallbackQuery(args.get("queryID"), "Message wasn't meant for you :P", true);
            return;
        }
        if (allBattles[uid]->chat->showSwapMessage.find(uid) != allBattles[uid]->chat->showSwapMessage.end() && allBattles[uid]->chat->showSwapMessage[uid]) {
            allBattles[uid]->chat->showSwapMessage[uid] = false;
        } else {
            allBattles[uid]->chat->showSwapMessage[uid] = true;
        }
        allBattles[uid]->UpdateKeyboard();
    }
}