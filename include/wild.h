#ifndef WILD_H
#define WILD_H

#include "pokemon.h"

class Wild {
    private:
        Pokemon pokemon;

    public:
        Wild(Pokemon);
        Wild() = default;
};

#endif