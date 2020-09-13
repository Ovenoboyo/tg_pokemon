#ifndef BATTLE_H
#define BATTLE_H

#include <unordered_map> // for unordered_map
#include <vector>        // for vector

#include "pokemon/player.h" // for UID

class BaseBattle;

/**
 * @brief Global holder for battles
 *
 */
inline std::unordered_map<UID, BaseBattle *> allBattles;

/**
 * @brief Adds BaseBattle Object to global holder
 *
 */
void registerBattle(UID, BaseBattle *);

/**
 * @brief Removes BaseBattle object from global holder and deallocate them
 *
 */
void deregisterBattle(BaseBattle *, std::vector<UID>);

/**
 * @brief Checks if battle is active
 *
 * @return true if UID corresponds to a BaseBattle object
 * @return false if UID does not corresponds to a BaseBattle object
 */
bool isBattleActive(UID);

#endif
