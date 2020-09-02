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

Player *FetchPlayer() {
    auto pokemon1 = FetchPokemon(); 

    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    auto player = new Player(boost::uuids::to_string(uuid), "player", MALE);
    player->addPokemonInTeam(pokemon1);

    return player;
}