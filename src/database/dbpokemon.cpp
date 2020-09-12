#include "pokemon/database/dbpokemon.h"
#include "pokemon/pokemon.h"

Pokemon *FetchPokemon() {
  Stats basestats(130, 85, 80, 85, 95, 60), IV(3, 26, 7, 7, 11, 18),
      EV(134, 141, 14, 24, 65, 132);
  ElementType types[2] = {WATER, ICE};
  MoveSet moveset = {Move("Tackle", NORMAL, 40, 100, 32), Move(), Move(),
                     Move()};

  return new Pokemon("Lapras", types, 74, moveset, basestats, IV, EV);
}