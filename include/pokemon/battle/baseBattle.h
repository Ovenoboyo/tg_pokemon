#ifndef BASEBATTLE_H
#define BASEBATTLE_H

#include <stdint.h>      // for int32_t
#include <string>        // for string
#include <unordered_map> // for unordered_map

#include "pokemon/moves.h"  // for Move
#include "pokemon/user/player.h" // for Player (ptr only), UID

struct DamageCalcHolder
{
    // Attacker
    int AttackerLevel;
    int AttackStat;
    int power;

    // Defender
    int DefenderLevel;
    int DefenceStat;

    // Modifiers
    float attackModifier;
    float typeModifier;
};

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
    ChatInfo *chat;

    /**
     * @brief The most recently played moves for each player
     *
     */
    std::unordered_map<UID, Move *> playedMove;

    /**
     * @brief Calculates damage by attacker on defender
     *
     * @param attacker Player who's pokemon attacks
     * @param defender player against whom the damage is to be calculated
     * @return int value of damage to be dealt
     */
    int calculateDamage(struct DamageCalcHolder holder);

    /**
     * @brief First Player
     *
     */
    Player *player1;

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
     * @brief Handles player moves, swap and roundEndCounter
     *
     * @param uid UID of player
     * @param moveNo Index of move ranging from 1-4 or Index of swap ranging
     * from 1-6
     * @param swap bool to check if move is swap or attack
     */
    virtual void HandlePlayerChoice(UID uid, int moveNo, bool swap);

    /**
     * @brief Handle events at start of new round
     *
     */
    virtual void HandleRoundStart();

    /**
     * @brief Handle events at end of round. Includes checking if player is
     * defeated.
     *
     */
    virtual void HandleRoundEnd();

    void HandleBattle(UID uid, int moveNo, bool swap);
    void HandleBattle();
};

float getAttackModifier(std::vector<ElementType> pkType, ElementType akType);
bool isDefeated(Player *player);

#endif
