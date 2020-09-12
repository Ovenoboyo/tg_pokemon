#ifndef Player_H
#define Player_H

#include <string>
#include <vector>
#include "pokemon.h"

class Pokemon;

typedef int32_t UID;

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
  std::vector<Pokemon *> Team;

  // Bag of items
  Bag bag;

  // Use when pokemon swap is to be forcibly carried out
  bool isSwapping;

  int FntCount;

  Player(UID uid, std::string name, enum Genders gender,
         std::vector<Pokemon *> team);
  Player() = default;
};

#endif
