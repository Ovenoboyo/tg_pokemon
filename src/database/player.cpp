#include "player.h"
#include "database/dbplayer.h"
#include "database/dbpokemon.h"
#include <string>

class Pokemon;

Player *FetchPlayer(std::string uid) {
  auto pokemon1 = FetchPokemon();
  Pokemon *team[6] = {pokemon1};

  auto player = new Player(uid, "player", MALE, team);

  return player;
}