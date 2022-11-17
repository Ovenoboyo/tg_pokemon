#ifndef Pokemon_H
#define Pokemon_H

#include <string> // for string
#include <vector> // for vector

#include "pokemon/global.h" // for ElementType

class Move;

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

    std::string Serialize();
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
     * @brief Vector holding Type for pokemon
     *
     */
    std::vector<ElementType> type;

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
    std::vector<Move *> Moveset;

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
    Pokemon(std::string name, std::vector<ElementType> types, int level,
            std::vector<Move *> moveset, Stats baseStats, Stats IVStats,
            Stats EVStats);

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
Stats generateIV();

#endif
