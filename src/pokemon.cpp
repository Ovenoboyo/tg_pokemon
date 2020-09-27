#include "pokemon/pokemon.h"

#include <fmt/core.h> // for format
#include <random>     // for mt19937, uniform_int_distribution, random_device

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
    this->Health =
        getStat(baseStats.MaxHP, IVStats.MaxHP, EVStats.MaxHP, level, true);

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

std::string Stats::Serialize() {
    return fmt::format("{0}, {1}, {2}, {3}, {4}, {5}", this->MaxHP,
                       this->Attack, this->Defence, this->SPAttack,
                       this->SPDefence, this->Speed);
}

int getStat(int base, int iv, int ev, int level, bool isHP) {
    if (!isHP) {
        return int(((((base + iv) * 2) + (ev / 4)) * level) / 100) + 5;
    } else {
        // TODO: HP Stats logic
        return int(((((base + iv) * 2) + (ev / 4)) * level) / 100) + level + 10;
    }
}

Stats generateIV() {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> distribution(1, 31);

    return Stats(distribution(random_engine), distribution(random_engine),
                 distribution(random_engine), distribution(random_engine),
                 distribution(random_engine), distribution(random_engine));
}
