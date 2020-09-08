#include "database/dbplayer.h"
#include "database/dbplayer.h"
#include "database/dbpokemon.h"
#include "pokemon.h"
#include "player.h"
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp> 
#include <string>

Player *FetchPlayer(std::string uid) {
    auto pokemon1 = FetchPokemon(); 

    auto player = new Player(uid, "player", MALE);
    player->addPokemonInTeam(pokemon1);

    return player;
}