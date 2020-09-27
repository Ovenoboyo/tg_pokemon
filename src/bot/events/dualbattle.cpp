#include "pokemon/bot/events/dualbattle.h"
#include "pokemon/battle/battle.h"
#include "pokemon/battle/dualBattle.h"
#include "pokemon/database/conn.h"
#include "pokemon/user/player.h"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string.hpp>
#include <memory>
#include <tgbot/tgbot.h>

void RegisterRequest(int32_t p1, int32_t p2) {
    if (allRequests.find(p1) != allRequests.end() &&
        allRequests.find(p2) != allRequests.end()) {
        allRequests.insert(std::pair<int32_t, int32_t>(p1, p2));
        return;
    }
    throw InBattleException();
}

void DeregisterRequest(int32_t p1) {
    if (allRequests.find(p1) != allRequests.end()) {
        allRequests.erase(p1);
    }
}

int32_t GetRequested(int32_t requester) {
    if (allRequests.find(requester) != allRequests.end()) {
        return allRequests[requester];
    }
    return INVALID_ID;
}

bool HasRequested(int32_t requester) {
    return allRequests.find(requester) != allRequests.end();
}

std::shared_ptr<Player> GetPlayerByID(int32_t id) {
    try {
        auto player1 = dbConn->FetchPlayer(id);
        return player1;
    } catch (const std::exception &e) {
        std::cout << e.what();
        return std::make_shared<Player>();
    }
}

DualBattle *GetDualBattle(std::shared_ptr<Player> p1,
                          std::shared_ptr<Player> p2,
                          TgBot::Message::Ptr message) {
    DualBattle *battle;
    if (message->chat->type == TgBot::Chat::Type::Group) {
        battle = new DualBattle(p1, p2, message->chat->id);
    } else {
        battle = new DualBattle(p1, p2, INVALID_ID);
    }
    return battle;
}

void RegisterForBoth(DualBattle *battle, int32_t p1, int32_t p2) {
    registerBattle(p1, battle);
    registerBattle(p2, battle);
}

int32_t getIDFromUsername(std::string username) {
    boost::algorithm::trim(username);
    if (StringTools::startsWith(username, "@")) {
        // Removes @
        username.erase(0, 1);
    }
    return dbConn->isPlayerRegistered(username);
}

void validateAndStartBattle(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    auto requester = message->from->id;
    if (HasRequested(requester)) {
        auto requested = GetRequested(requester);
        if (!isBattleActive(requester) && !isBattleActive(requested)) {
            auto player1 = GetPlayerByID(requester);
            auto player2 = GetPlayerByID(requested);

            if (player1->isEmpty || player2->isEmpty) {
                bot.getApi().sendMessage(message->chat->id,
                                         "Either of the users not registered");
                return;
            }

            auto battle = GetDualBattle(player1, player2, message);
            RegisterForBoth(battle, player1->Uid, player2->Uid);
            battle->HandleRoundStart();
        } else {
            bot.getApi().sendMessage(message->chat->id,
                                     "Player already in battle");
        }
    }
}

void AskBattleCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    std::vector<std::string> args;
    boost::split(args, message->text, [](char c){return c == ' ';});
    if (args.size() > 0) {
        int32_t requesterID = message->from->id;
        int32_t requestedID = getIDFromUsername(args.at(0));

        if (requestedID != INVALID_ID) {
            try {
                RegisterRequest(requestedID, requesterID);
            } catch (const InBattleException &e) {
                bot.getApi().sendMessage(message->chat->id, e.what());
                return;
            }
            bot.getApi().sendMessage(message->chat->id, "@" + args.at(0) +
                                                            " Type yes to accept");
        } else {
            bot.getApi().sendMessage(message->chat->id, "No such user");
        }
    }
}