#include "pokemon/bot/events/events.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <tgbot/tgbot.h>

#include "pokemon/battleHolder.h"
#include "pokemon/bot/bot.h"
#include "pokemon/database/dbplayer.h"
#include "pokemon/global.h"
#include "pokemon/moves.h"
#include "pokemon/player.h"
#include "pokemon/pokemon.h"
#include "pokemon/bot/events/battleRequest.h"

const int32_t INVALID_ID = -1;


void StartCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) {
  bot.getApi().sendMessage(message->chat->id, "Hi!");
}

void validateAndStartBattle(TgBot::Bot &bot, TgBot::Message::Ptr message) {
  auto it = allRequests.find(message->from->id);
  if (it != allRequests.end()) {
    auto player1 = FetchPlayer(allRequests[message->from->id]);
    auto player2 = FetchPlayer(message->from->id);

    BattleHolder *battle;

    if (message->chat->type == TgBot::Chat::Type::Group) {
      battle = generateBattle(player1, player2, message->chat->id);
    } else {
      battle = generateBattle(player1, player2, -1);
    }

    if (!isBattleActive(player1->Uid) && !isBattleActive(player2->Uid)) {
      registerBattle(player1->Uid, battle);
      registerBattle(player2->Uid, battle);

    } else {
      bot.getApi().sendMessage(message->chat->id, "Player already in battle");
    }

  }
}

void AskBattleCommand(TgBot::Bot &bot, TgBot::Message::Ptr message) {
  std::string requestedUsername = message->text.substr(7);

  boost::algorithm::trim(requestedUsername);
  if (StringTools::startsWith(requestedUsername, "@")) {
    // Removes @
    requestedUsername.erase(0, 1);
  }

  int32_t requesterID = message->from->id;
  int32_t requestedID = isPlayerRegistered(requestedUsername);

  if (requestedID != INVALID_ID) {
    allRequests.insert(std::pair<int32_t, int32_t>(requestedID, requesterID));
    bot.getApi().sendMessage(message->chat->id, "@" + requestedUsername + " Type yes to accept");
  } else {
    bot.getApi().sendMessage(message->chat->id, "No such user");
  }
}

void sendMessages(TgBot::Bot &bot, int32_t chatIDs, std::string message) {
  bot.getApi().sendMessage(chatIDs, message);
}

void registerTextCommands(TgBot::Bot &bot) {
  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    boost::algorithm::to_lower(message->text);
    if (message->text.compare("attack") == 0) {
      UID uid = message->from->id;
      std::unordered_map<UID, BattleHolder *>::iterator it = allBattles.find(uid);
      if (it != allBattles.end()) {
        auto battle = it->second;

        battle->HandlePlayerChoice(uid, 1, false);
        battle->HandlePlayerChoice(2, 1, false);
      }
    }
  });
}

void handlePlayerAttack(TgBot::Message::Ptr message) {
  if (allBattles.find(message->from->id) != allBattles.end()) {
    auto battle = allBattles[message->from->id];

    battle->HandlePlayerChoice(message->from->id, 1, false);
  }
}

void registerCommands(TgBot::Bot &bot) {
  std::vector<TgBot::BotCommand::Ptr> commands;
  TgBot::BotCommand::Ptr cmdArray(new TgBot::BotCommand);

  cmdArray->command = "battle";
  cmdArray->description = "Initiate a battle";
  commands.push_back(cmdArray);

  bot.getApi().setMyCommands(commands);
}

void handleCommands(TgBot::Bot &bot) {
  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    if (StringTools::startsWith(message->text, "/start")) {
      StartCommand(bot, message);
    } else if (StringTools::startsWith(message->text, "/battle")) {
      AskBattleCommand(bot, message);
    } else if (message->text == "yes") {
      validateAndStartBattle(bot, message);
    } else if (message->text == "attack") {
      handlePlayerAttack(message);
    }
  });
}
