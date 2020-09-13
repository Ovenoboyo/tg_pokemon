#include "pokemon/database/dbplayer.h"
#include "pokemon/database/dbpokemon.h" // for FetchPokemon
#include "pokemon/player.h"             // for UID, MALE, Player
#include <string>                       // for allocator, string
#include <vector>                       // for vector

class Pokemon;

Player *FetchPlayer(UID uid) {
  auto pokemon1 = FetchPokemon();
  std::vector<Pokemon *> team = {pokemon1};

  auto player = new Player(uid, "player", MALE, team);

  return player;
}

UID isPlayerRegistered(std::string username) { return 609604248; }