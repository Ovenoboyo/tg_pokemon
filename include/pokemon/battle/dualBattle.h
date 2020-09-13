#ifndef DUALBATTLE_H
#define DUALBATTLE_H

#include <stdint.h> // for int32_t
#include <string>   // for string

#include "pokemon/battle/baseBattle.h" // for BaseBattle
#include "pokemon/moves.h"             // for Move
#include "pokemon/player.h"            // for Player (ptr only), UID

class DualBattle : public BaseBattle {
public:
  Player *player2;

  DualBattle(Player *p1, Player *p2, int32_t groupID);

  Player *GetOtherPlayer(UID uid);

  Player *GetPlayer(UID uid);

  /**
   * @brief Calculate damage and apply it to respective pokemons
   *
   */
  void ApplyMoves();

  /**
   * @brief Generates a summary of current battle progress
   *
   * @return std::string summary
   */
  std::string generateBattleSummary();

  /**
   * @brief Get move summary for specified player
   *
   * @param player Player object
   * @return std::string summary
   */
  std::string generateMoveSummary(Player player);

  /**
   * @brief Generates a summary of valid swappable pokemons
   *
   * @param player Player object
   * @return std::string summary
   */
  std::string generateSwapSummary(Player player);

  void sendSwapReport(UID uid);

  /**
   * @brief Handles player moves, swap and roundEndCounter
   *
   * @param uid UID of player
   * @param moveNo Index of move ranging from 1-4 or Index of swap ranging from
   * 1-6
   * @param swap bool to check if move is swap or attack
   */
  void HandlePlayerChoice(UID uid, int moveNo, bool swap);

  /**
   * @brief Handle events at start of new round
   *
   */
  void HandleRoundStart();

  /**
   * @brief Handle events at end of round. Includes checking if player is
   * defeated.
   *
   */
  void HandleRoundEnd();

  /**
   * @brief Swap 2 pokemon in team
   *
   * @param uid UID of player
   * @param index Index of pokemon to be swapped with Index 0
   */
  void SwapPokemon(UID uid, int index);

  /**
   * @brief Get the Move corresponding to index
   *
   * @return Move
   */
  Move getMoveFromIndex(Player player, int moveNo);
};

#endif