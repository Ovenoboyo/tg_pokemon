#include "database/dbplayer.h"
#include "database/dbpokemon.h"
#include "player.h"
#include <string>

class Pokemon;

Player *FetchPlayer(UID uid) {
  auto pokemon1 = FetchPokemon();
  std::vector<Pokemon *> team = {pokemon1};

  auto player = new Player(uid, "player", MALE, team);

  return player;
}

UID isPlayerRegistered(std::string username) {
  return 609604248;
}