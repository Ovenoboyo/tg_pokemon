#include "pokemon/bot/events/starters.h"

#include <cstdint> // for int32_t
#include <memory>  // for __shared_ptr_access
#include <string>  // for operator+, string, cha...
#include <utility> // for pair
#include <vector>  // for vector

#include "pokemon/database/conn.h"            // for PGConn, dbConn, starte...
#include "tgbot/Api.h"                        // for Api
#include "tgbot/Bot.h"                        // for Bot
#include "tgbot/EventBroadcaster.h"           // for EventBroadcaster
#include "tgbot/tools/StringTools.h"          // for startsWith
#include "tgbot/types/CallbackQuery.h"        // for CallbackQuery, Callbac...
#include "tgbot/types/Chat.h"                 // for Chat, Chat::Ptr
#include "tgbot/types/InlineKeyboardButton.h" // for InlineKeyboardButton::Ptr
#include "tgbot/types/InlineKeyboardMarkup.h" // for InlineKeyboardMarkup
#include "tgbot/types/Message.h"              // for Message, Message::Ptr
#include "tgbot/types/User.h"                 // for User, User::Ptr

void sendStarterMessage(TgBot::Bot &bot, int32_t chatID, UID uid) {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row0;
    TgBot::InlineKeyboardButton::Ptr checkButton(
        new TgBot::InlineKeyboardButton);

    std::string ret = "";
    int i = 0;
    auto starters = dbConn->getStarters();
    for (auto s : starters) {
        checkButton->text = s.name;
        checkButton->callbackData = "starter-" + std::to_string(i);
        row0.push_back(checkButton);
        i++;
    }

    keyboard->inlineKeyboard.push_back(row0);
    auto messageIdBot = bot.getApi()
                            .sendMessage(chatID, "Select Starter...", true, 0,
                                         keyboard, "Markdown")
                            ->messageId;
    starterMessages.insert(std::pair<UID, int32_t>(uid, messageIdBot));
}

void handleStarterCallback(TgBot::Bot &bot) {
    bot.getEvents().onCallbackQuery([&bot](TgBot::CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "starter-")) {
            auto it = starterMessages.find(query->from->id);
            if (it != starterMessages.end()) {
                auto selected =
                    dbConn->getStarters().at(std::stoi(query->data.substr(8)));

                // TODO: Register selected pokemon
                dbConn->registerStarter(query->from->id, query->from->username,
                                        selected.pokedex_no, MALE);

                std::string response = "You chose " + selected.name;

                bot.getApi().deleteMessage(query->message->chat->id,
                                           starterMessages.at(query->from->id));
                starterMessages.erase(it);

                bot.getApi().sendMessage(query->message->chat->id, response);
            }
        }
    });
}

void pickStarter(TgBot::Bot &bot, TgBot::Message::Ptr message) {
    sendStarterMessage(bot, message->chat->id, message->from->id);
}
