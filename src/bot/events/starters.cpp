#include "pokemon/bot/events/starters.h"

#include <cstdint> // for int32_t
#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for stoi, operator+, string, char_traits, to_string, basic_string
#include <utility> // for pair
#include <vector>  // for vector

#include "pokemon/database/conn.h"            // for PGConn, dbConn, starterHolder
#include "pokemon/global.h"                   // for BotArgs
#include "pokemon/user/player.h"              // for UID, MALE
#include "tgbot/Api.h"                        // for Api
#include "tgbot/Bot.h"                        // for Bot
#include "tgbot/types/Chat.h"                 // for Chat, Chat::Ptr
#include "tgbot/types/InlineKeyboardButton.h" // for InlineKeyboardButton::Ptr, InlineKeyboardButton
#include "tgbot/types/InlineKeyboardMarkup.h" // for InlineKeyboardMarkup, InlineKeyboardMarkup::Ptr
#include "tgbot/types/Message.h"              // for Message, Message::Ptr
#include "tgbot/types/User.h"                 // for User, User::Ptr

void sendStarterMessage(TgBot::Bot &bot, int32_t chatID, UID uid) {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row0;
    TgBot::InlineKeyboardButton::Ptr checkButton(new TgBot::InlineKeyboardButton);

    std::string ret = "";
    int i = 0;
    auto starters = dbConn->getStarters();
    for (auto s : starters) {
        checkButton->text = s.name;
        checkButton->callbackData = "type=starterCallback,starter=" + std::to_string(i);
        row0.push_back(checkButton);
        i++;
    }

    keyboard->inlineKeyboard.push_back(row0);
    auto messageIdBot = bot.getApi().sendMessage(chatID, "Select Starter...", true, 0, keyboard, "Markdown")->messageId;
    starterMessages.insert(std::pair<UID, int32_t>(uid, messageIdBot));
}

void starterCallback(TgBot::Bot &bot, BotArgs args) {
    auto fromID = std::stoi(args.get("queryFromID"));
    auto it = starterMessages.find(fromID);
    if (!dbConn->isPlayerRegistered(fromID) && it != starterMessages.end()) {
        auto fromUsername = args.get("queryFromUsername");
        auto fromChatID = std::stoi(args.get("queryChatID"));

        auto selected = dbConn->getStarters().at(std::stoi(args.get("starter")));

        dbConn->registerStarter(fromID, fromUsername, selected.pokedex_no, MALE);

        std::string response = "You chose " + selected.name;

        bot.getApi().deleteMessage(fromChatID, starterMessages.at(fromID));
        bot.getApi().sendMessage(fromChatID, response);

        starterMessages.erase(it);
    } else {
        bot.getApi().answerCallbackQuery(args.get("queryID"), "Message expired or invalid...");
    }
}

void pickStarter(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    sendStarterMessage(bot, message->chat->id, message->from->id);
}
