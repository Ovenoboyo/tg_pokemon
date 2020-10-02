#include "pokemon/global.h"

#include <boost/algorithm/string/classification.hpp>         // for is_any_of
#include <boost/algorithm/string/detail/classification.hpp>  // for is_any_ofF
#include <boost/algorithm/string/split.hpp>                  // for split
#include <boost/iterator/iterator_facade.hpp>                // for operator!=
#include <boost/range/distance.hpp>                          // for distance
#include <boost/type_index/type_index_facade.hpp>            // for operator==
#include <stdlib.h>                                          // for getenv, NULL
#include <memory>                                            // for __shared_ptr_access
#include <unordered_map>                                     // for unordered_map, unordered_map<>::mapped_type, operator!=
#include <vector>                                            // for vector

#include "tgbot/types/Chat.h"                                // for Chat, Chat::Ptr
#include "tgbot/types/Message.h"                             // for Message, Message::Ptr
#include "tgbot/types/User.h"                                // for User, User::Ptr


std::string getEnvVar(std::string const &key) {
  char const *val = getenv(key.c_str());
  return val == NULL ? std::string() : std::string(val);
}

void BotArgs::parseCallbackData(std::string data) {
  std::vector<std::string> tmp;
  boost::split(tmp, data, boost::is_any_of(","));
  for (auto i : tmp) {
    std::vector<std::string> tmp1;
    boost::split(tmp1, i, boost::is_any_of("="));
    if (tmp.size() == 2) {
      this->args[tmp1.at(0)] = tmp1.at(1);
    }
  }
}

void BotArgs::parseQueryDetails(TgBot::CallbackQuery::Ptr query) {
    this->args["queryFromID"] = std::to_string(query->from->id);
    this->args["queryFromUsername"] = query->from->username;
    this->args["queryChatID"] = std::to_string(query->message->chat->id);
    this->args["queryID"] = query->id;
    this->parseCallbackData(query->data);
}

std::string BotArgs::get(std::string i, std::string def) {
    if (this->args.find(i) != this->args.end()) {
        return this->args.at(i);
    }
    return def;
}

int BotArgs::size() {
    return this->args.size();
}