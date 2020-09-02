#ifndef Pokemon_H
#define Pokemon_H

#include<string>
#include "moves.h"
#include "global.h"

typedef int Stat; 

struct Stats
{
    Stat MaxHP;
    Stat Attack;
    Stat Defence;
    Stat SPAttack;
    Stat SPDefence;
    Stat Speed;
};

struct MoveSet {
    Move move1;
    Move move2;
    Move move3;
    Move move4;
};

class Pokemon {
    private:
        // Calculation vars
        Stats baseStats;
        ElementType type[2];

    public:
        std::string Nickname;
        std::string IconPath;
        MoveSet Moveset;
        Stat Health;

        Pokemon(std::string, Stats, ElementType *, MoveSet);
        Pokemon() = default;

};

#endif
