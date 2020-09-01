#include <tgbot/tgbot.h>
#include "bot/events/events.h"

#include "player.h"
#include "pokemon.h"
#include "moves.h"
#include "battleHolder.h"
#include "global.h"

void startCommand(TgBot::Bot* bot) {
    bot->getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot->getApi().sendMessage(message->chat->id, "Hi!");
    });
}

void battleCommand(TgBot::Bot* bot) {
    bot->getEvents().onCommand("battle", [&bot](TgBot::Message::Ptr message) {
        Stats stats = {1, 1, 1, 1 ,1 ,1};
        ElementType types[2];
        types[0] = FLYING;
        Move moveset[4] = {Move("move1", GROUND, 5, 50, 100)};

        Pokemon pokemon1("pokeman", stats, types, moveset);
        Player player1("1", "player1", MALE);
        player1.addPokemonInTeam(pokemon1);

        Pokemon pokemon2("pokeman", stats, types, moveset);
        Player player2("2", "player2", FEMALE);
        player2.addPokemonInTeam(pokemon2);

        BattleHolder battle(player1, player2);
        bot->getApi().sendMessage(message->chat->id, battle.FirstMove());
        //std::cout << battle.FirstMove().getUID();
    });
}
