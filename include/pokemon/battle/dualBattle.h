#ifndef DUALBATTLE_H
#define DUALBATTLE_H

#include <memory>        // for shared_ptr
#include <stdint.h>      // for int32_t
#include <string>        // for string
#include <unordered_map> // for unordered_map
#include <vector>        // for vector

#include "pokemon/battle/baseBattle.h"        // for BaseBattle, DamageCalcHolder (ptr only)
#include "pokemon/user/player.h"              // for Player (ptr only), UID
#include "tgbot/types/InlineKeyboardButton.h" // for InlineKeyboardButton, InlineKeyboardButton::Ptr

class Move;
class Pokemon;

class DualBattle : public BaseBattle {
  public:
    Player::Ptr player2;

    DualBattle(Player::Ptr p1, Player::Ptr p2, int32_t groupID);

    Player::Ptr GetOtherPlayer(UID uid);

    Player::Ptr GetPlayer(UID uid);

    DamageCalcHolder *getStats(Pokemon attacker, Pokemon defender, Move Move);

    bool isRoundEnd();

    void resetPlayerPlayed();

    void UpdateKeyboard();

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
    std::vector<TgBot::InlineKeyboardButton::Ptr> generateMoveSummary(Player player);

    /**
     * @brief Generates a summary of valid swappable pokemons
     *
     * @param player Player object
     * @return std::string summary
     */
    std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> GenerateSwapReport(UID uid);

    void sendSwapReport(UID uid);
    std::vector<TgBot::InlineKeyboardButton::Ptr> generateExtraRow(Player player);

    /**
     * @brief Handles player moves, swap and roundEndCounter
     *
     * @param uid UID of player
     * @param moveNo Index of move ranging from 1-4 or Index of swap ranging
     * from 1-6
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

    void handleMessages();

    /**
     * @brief Calculate damage and apply it to respective pokemons
     *
     */
    void ApplyMoves();

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
    Move *getMoveFromIndex(Player player, int moveNo);
};

#endif