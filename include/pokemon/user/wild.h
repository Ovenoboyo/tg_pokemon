#ifndef WILD_H
#define WILD_H

#include <memory>
#include "pokemon/pokemon.h"

class Wild {
  public:
    Pokemon::Ptr pokemon;

    Wild(Pokemon::Ptr p);
    Wild() = default;
};

#endif
