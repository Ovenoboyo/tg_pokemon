#include "box.h"
#include "pokemon.h"

bool Box::addPokemonInBox(Pokemon p) {
  if (Box::pokemonCount < 30) {
    this->pokemons[pokemonCount] = p;
    return true;
  }
  return false;
}

Pokemon Box::getPokemonInBox(int i) { return this->pokemons[i]; }