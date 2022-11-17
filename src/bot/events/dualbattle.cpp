#include "pokemon/bot/events/dualbattle.h"

#include <boost/algorithm/string/classification.hpp>         // for is_any_of
#include <boost/algorithm/string/detail/classification.hpp>  // for is_any_ofF
#include <boost/algorithm/string/split.hpp>                  // for split
#include <boost/algorithm/string/trim.hpp>                   // for trim
#include <boost/iterator/iterator_facade.hpp>                // for operator!=
#include <boost/range/distance.hpp>                          // for distance
#include <boost/type_index/type_index_facade.hpp>            // for operator==
#include <fmt/core.h>                                        // for format
#include <cstdint>                                           // for int32_t
#include <iostream>                                          // for operator<<, cout, ostream
#include <memory>                                            // for allocator, __shared_ptr_access, shared_ptr
#include <string>                                            // for string, operator+, char_traits, basic_string
#include <utility>                                           // for pair
#include <vector>                                            // for vector

#include "pokemon/battle/battle.h"                           // for isBattleActive, registerBattle
#include "pokemon/battle/dualBattle.h"                       // for DualBattle
#include "pokemon/database/conn.h"                           // for NotRegisteredException, PGConn, dbConn
#include "pokemon/user/player.h"                             // for INVALID_ID, Player
#include "tgbot/Api.h"                                       // for Api
#include "tgbot/Bot.h"                                       // for Bot
#include "tgbot/tools/StringTools.h"                         // for startsWith
#include "tgbot/types/Chat.h"                                // for Chat, Chat::Ptr, Chat::Type, Chat::Type::Group
#include "tgbot/types/User.h"                                // for User, User::Ptr

void RegisterRequest(int32_t p1, int32_t p2) {
    if (allRequests.find(p1) == allRequests.end() &&
        allRequests.find(p2) == allRequests.end()) {
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
    auto player1 = dbConn->FetchPlayer(id);
    return player1;
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
            try {
                auto player1 = GetPlayerByID(requester);
                auto player2 = GetPlayerByID(requested);

                auto battle = GetDualBattle(player1, player2, message);
                RegisterForBoth(battle, player1->Uid, player2->Uid);
                battle->HandleBattleInit();
            } catch (const NotRegisteredException &e) {
                std::cout << e.what();
                bot.getApi().sendMessage(message->chat->id,
                                            fmt::format("player {} not registered", e.what()));
                return;
            }
        } else {
            bot.getApi().sendMessage(message->chat->id,
                                     "Player already in battle");
        }
    }
}

void AskBattleCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    std::vector<std::string> args;
    boost::split(args, message->text, boost::is_any_of(" "));
    if (args.size() > 0) {
        int32_t requesterID = message->from->id;
        int32_t requestedID = getIDFromUsername(args.at(1));

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