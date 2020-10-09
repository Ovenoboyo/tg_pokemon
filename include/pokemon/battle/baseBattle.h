#ifndef BASEBATTLE_H
#define BASEBATTLE_H

#include <stdint.h>                            // for int32_t
#include <list>                                // for list
#include <memory>                              // for shared_ptr
#include <string>                              // for string
#include <unordered_map>                       // for unordered_map
#include <vector>                              // for vector

#include "pokemon/global.h"                    // for ElementType
#include "pokemon/user/player.h"               // for UID, Player, Player::Ptr
#include "tgbot/types/InlineKeyboardButton.h"  // for InlineKeyboardButton, InlineKeyboardButton::Ptr

class Move;
class Pokemon;

struct DamageCalcHolder {
    typedef std::shared_ptr<DamageCalcHolder> Ptr;
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

    std::unordered_map<int32_t, std::vector<int32_t>> prevMessages;
    std::unordered_map<int32_t, int32_t> battleMessage;
    std::unordered_map<UID, bool> showSwapMessage;

    ChatInfo(int32_t botReportID);
};

class BaseBattle {
  public:
    ChatInfo *chat;

    bool isEnd;

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
    std::unordered_map<UID, Player::Ptr> players;

    /**
     * @brief Construct a new Battle Holder object
     *
     * @param p1 Player 1
     * @param com Pokemon in Wild
     * @param groupID -1 if valid
     */
    BaseBattle(std::list<Player::Ptr> players, int32_t groupID);

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

    Player::Ptr GetPlayer(UID uid);

    Player::Ptr GetOtherPlayer(UID uid);

    /**
     * @brief Handle events at end of round. Includes checking if player is
     * defeated.
     *
     */
    virtual void HandleRoundEnd();

    virtual void UpdateKeyboard();

    Move *GetMoveFromIndex(Player player, int moveNo);

    DamageCalcHolder::Ptr getStats(Pokemon attacker, Pokemon defender, Move move);
    void ApplyMoves();

    std::vector<TgBot::InlineKeyboardButton::Ptr> GenerateMoveSummary(Player player);
    std::vector<std::vector<TgBot::InlineKeyboardButton::Ptr>> GenerateSwapReport(UID uid);
    std::string GenerateBattleSummary();
    std::vector<TgBot::InlineKeyboardButton::Ptr> GenerateExtraRow(UID uid);

    void SwapPokemon(UID uid, int index);
    void sendSwapReport(UID uid);

    void HandleBattle(UID uid, int moveNo, bool swap);
    void HandleBattleInit();
    void cleanMessages(UID chatID);
};

float getAttackModifier(std::vector<ElementType> pkType, ElementType akType);
bool isDefeated(Player::Ptr player);

#endif
