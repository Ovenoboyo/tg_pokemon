#ifndef Player_H
#define Player_H

#include "box.h"
#include "moves.h"
#include "pokemon.h"
#include <string>

typedef std::string UID;

enum Genders { MALE, FEMALE };

class Bag {
private:
  // TODO: Bag class
};

class Player {
public:
  // Unique ID
  UID Uid;

  // Name of player
  std::string Name;

  // Gender of player
  Genders Gender;

  // Team of pokemons
  Pokemon *Team[6];

  // Bag of items
  Bag bag;

  // Count of pokemons in team
  int teamCount;

  Player(UID uid, std::string name, enum Genders gender, Pokemon **team);
  Player() = default;
};

#endif
