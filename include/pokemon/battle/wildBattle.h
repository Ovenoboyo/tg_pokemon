#ifndef WILDBATTLE_H
#define WILDBATTLE_H

#include <stdint.h>                     // for int32_t
#include <list>                         // for list

#include "pokemon/battle/baseBattle.h"  // for BaseBattle
#include "pokemon/user/player.h"        // for Player, Player::Ptr, UID

class Move;

class WildBattle : public BaseBattle {
  public:

    WildBattle(std::list<Player::Ptr> players, int32_t groupID);

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

    void handleMessages(int32_t chatID);

    /**
     * @brief Handle events at end of round. Includes checking if player is
     * defeated.
     *
     */
    void HandleRoundEnd();

    /**
     * @brief Get the Move corresponding to index
     *
     * @return Move
     */
    Move *getMoveFromIndex(Player player, int moveNo);

    void UpdateKeyboard();
};

#endif