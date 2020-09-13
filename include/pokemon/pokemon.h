#ifndef Pokemon_H
#define Pokemon_H

#include "pokemon/global.h"
#include "pokemon/moves.h"
#include <string>

typedef int Stat;

/**
 * @brief Holds Stats for pokemon
 *
 */
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

/**
 * @brief Holds Moveset of pokemon
 *
 */
struct MoveSet {
  Move move1;
  Move move2;
  Move move3;
  Move move4;
};

class Pokemon {
public:
  /**
   * @brief Nickname of pokemon (User defined)
   *
   */
  std::string Nickname;

  std::string IconPath;

  /**
   * @brief Array holding Type for pokemon
   *
   */
  ElementType type[2];

  /**
   * @brief Base stats of pokemon
   *
   */
  Stats baseStats;

  /**
   * @brief IV Stats of pokemon
   *
   */
  Stats IVStats;

  /**
   * @brief EV Stats of pokemon
   *
   */
  Stats EVStats;

  /**
   * @brief Moveset of pokemon
   *
   */
  MoveSet Moveset;

  /**
   * @brief Calculated Health of pokemon
   *
   */
  Stat Health;

  /**
   * @brief Level of pokemon
   *
   */
  int Level;

  /**
   * @brief Bool to check if pokemon is fainted or not
   *
   */
  bool isFNT;

  /**
   * @brief Bool to check if pokemon is valid or not
   *
   */
  bool isEmpty;

  /**
   * @brief Construct a new Pokemon object
   *
   * @param name Name of pokemon
   * @param types Array of ElementType of pokemon
   * @param level Level of pokemon
   * @param moveset Moveset of pokemon
   * @param baseStats BaseStats of pokemon
   * @param IVStats IVstats of pokemon
   * @param EVStats EVstats of pokemon
   */
  Pokemon(std::string name, ElementType *types, int level, MoveSet moveset,
          Stats baseStats, Stats IVStats, Stats EVStats);

  /**
   * @brief Construct a new Pokemon object
   *
   */
  Pokemon();
};

/**
 * @brief Get Calculated Stats
 *
 * @param base BaseStats of corresponsing stat
 * @param iv IVStats of corresponsing stat
 * @param ev EVStats of corresponsing stat
 * @param level Level of pokemon
 * @param isHP Bool to check if stat is HP or other
 * @return int Calulated stat
 */
int getStat(int base, int iv, int ev, int level, bool isHP);

#endif
