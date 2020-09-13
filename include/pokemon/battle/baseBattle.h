#ifndef BASEBATTLE_H
#define BASEBATTLE_H

#include <stdint.h>      // for int32_t
#include <string>        // for string
#include <unordered_map> // for unordered_map

#include "pokemon/moves.h"  // for Move
#include "pokemon/player.h" // for Player (ptr only), UID

const int32_t INVALID_ID = -1;

class ChatInfo {
public:
  /**
   * @brief ChatID of group if valid
   *
   */
  int32_t botReportID;

  /**
   * @brief True if messages are to be sent in Group
   *
   */
  bool isGroup;

  ChatInfo(int32_t botReportID);
};

class BaseBattle {
public:
  /**
   * @brief The most recently played moves for each player
   *
   */
  std::unordered_map<UID, Move> playedMove;

  ChatInfo *chat;

  /**
   * @brief Calculates damage by attacker on defender
   *
   * @param attacker Player who's pokemon attacks
   * @param defender player against whom the damage is to be calculated
   * @return int value of damage to be dealt
   */
  int calculateDamage(Player attacker, Player defender);

  /**
   * @brief First Player
   *
   */
  Player *player1;

  /**
   * @brief Counter which determines when all players have played their move.
   * Usually max at 2 and round ends at 0.
   *
   */
  int roundEndCounter;

  /**
   * @brief Construct a new Battle Holder object
   *
   * @param p1 Player 1
   * @param com Pokemon in Wild
   * @param groupID -1 if valid
   */
  BaseBattle(Player *p1, int32_t groupID);

  /**
   * @brief Destroy the Battle Holder object
   *
   */
  ~BaseBattle() = default;

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
   * @brief Checks if player is defeater
   *
   * @param player Reference to object of player
   * @return true If all pokemons of player are fainted
   * @return false If either of pokemons of player is alive
   */
  bool isDefeated(Player *player);

  /**
   * @brief Get the Move corresponding to index
   *
   * @return Move
   */
  Move getMoveFromIndex(Player, int);
};

#endif
