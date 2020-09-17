#ifndef WILD_H
#define WILD_H

#include "pokemon/pokemon.h"

class Wild {
  public:
    Pokemon *pokemon;

    Wild(Pokemon *p);
    Wild() = default;
};

#endif
