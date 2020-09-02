#ifndef Box_H
#define Box_H

#include "pokemon.h"

class Box{
    private:
        int pokemonCount;
        Pokemon pokemons[30];

    public:
        bool addPokemonInBox(Pokemon);
        Pokemon getPokemonInBox(int);

};
#endif