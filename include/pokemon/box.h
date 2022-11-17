#ifndef Box_H
#define Box_H

#include "pokemon/pokemon.h"

class Box {
  private:
    Pokemon pokemons[30];
    int pokemonCount;

  public:
    Pokemon getPokemonInBox(int);
};

#endif
