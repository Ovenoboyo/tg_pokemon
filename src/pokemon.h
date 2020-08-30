#include <string>

typedef int Stat; 

enum ElementType {NORMAL, FIGHT, FLYING, POISON, GROUND, ROCK, BUG, GHOST, FIRE, WATER, GRASS, ELECTRIC, PSYCH, ICE, DRAGON};

class Stats {
    private:
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
        ElementType type;
};