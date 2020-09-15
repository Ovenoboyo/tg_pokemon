#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

enum ElementType {
    NIL,
    NORMAL,
    FIGHT,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCH,
    ICE,
    DRAGON
};

std::string getEnvVar(std::string const &key);
#endif
