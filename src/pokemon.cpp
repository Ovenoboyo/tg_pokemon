#include "pokemon/pokemon.h"

class Move;

Pokemon::Pokemon(std::string name, std::vector<ElementType> types, int level,
                 std::vector<Move *> moveset, Stats baseStats, Stats IVStats,
                 Stats EVStats) {
    this->Nickname = name;
    this->baseStats = baseStats;
    this->EVStats = EVStats;
    this->IVStats = IVStats;
    this->Level = level;
    this->isFNT = false;

    // TODO: Work on health logic
    this->Health = baseStats.MaxHP;

    this->type.insert(this->type.end(), types.begin(), types.end());
    this->Moveset.insert(this->Moveset.end(), moveset.begin(), moveset.end());
}

Pokemon::Pokemon() {
    this->Nickname = "";
    this->baseStats = Stats();
    this->Moveset = std::vector<Move *>{};
    this->Health = 0;
    this->type.push_back(NIL);
    this->isEmpty = true;
}

Stats::Stats(Stat HP, Stat Attack, Stat Defence, Stat SPDefence, Stat SPAttack,
             Stat Speed) {
    this->MaxHP = HP;
    this->Speed = Speed;
    this->Attack = Attack;
    this->Defence = Defence;
    this->SPAttack = SPAttack;
    this->SPDefence = SPDefence;
}

int getStat(int base, int iv, int ev, int level, bool isHP) {
    if (!isHP) {
        // Stats = ([(Base + IV)*2 + EV/4] * level)/100 + 5
        return int(((((base + iv) * 2) + (ev / 4)) * level) / 100) + 5;
    } else {
        // TODO: HP Stats logic
        return 0;
    }
}
