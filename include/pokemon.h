#include<string>

#ifndef Pokemon_H
#define Pokemon_H

typedef int Stat; 

enum ElementType {NORMAL, FIGHT, FLYING, POISON, GROUND, ROCK, BUG, GHOST, FIRE, WATER, GRASS, ELECTRIC, PSYCH, ICE, DRAGON};

struct Stats
{
    Stat HP;
    Stat Attack;
    Stat Defence;
    Stat SPAttack;
    Stat SPDefence;
    Stat Speed;
};

class Pokemon {
    private:
        std::string Nickname;
        std::string IconPath;

        Stats baseStats;
        ElementType type[2];

        Move MoveSet;

    public:
        Pokemon(std::string, Stats, ElementType *, Move);
        Pokemon() = default;

        std::string getNickname();
};

#endif
