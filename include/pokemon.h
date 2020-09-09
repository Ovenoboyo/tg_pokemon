#ifndef Pokemon_H
#define Pokemon_H

#include "global.h"
#include "moves.h"
#include <string>

typedef int Stat;

struct Stats {
  Stat MaxHP;
  Stat Attack;
  Stat Defence;
  Stat SPAttack;
  Stat SPDefence;
  Stat Speed;

  Stats(Stat HP, Stat Attack, Stat Defence, Stat SPDefence, Stat SPAttack,
        Stat Speed);
  Stats() = default;
};

struct MoveSet {
  Move move1;
  Move move2;
  Move move3;
  Move move4;
};

class Pokemon {
public:
  std::string Nickname;
  std::string IconPath;
  ElementType type[2];

  Stats baseStats;
  Stats IVStats;
  Stats EVStats;

  MoveSet Moveset;
  Stat Health;

  int Level;

  bool isEmpty;

  Pokemon(std::string name, ElementType *types, int level, MoveSet moveset,
          Stats baseStats, Stats IVStats, Stats EVStats);
  Pokemon();
};

#endif
