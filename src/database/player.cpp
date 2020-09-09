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
    Pokemon* team[6] = {pokemon1};

    auto player = new Player(uid, "player", MALE, team);

    return player;
}