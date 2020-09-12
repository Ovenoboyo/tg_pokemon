#ifndef BATTLEHOLDER_H
#define BATTLEHOLDER_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <list>
#include <unordered_map>
#include <string>

#include "pokemon/player.h"
#include "pokemon/pokemon.h"
#include "pokemon/wild.h"

class BattleHolder {
private:
  Wild Com;
  std::unordered_map<UID, Move> playedMove;

  int32_t botReportID;
  bool isGroup;

  Move getMoveFromIndex(UID, int);

  void ApplyMoves();

  int calculateDamage(Player attacker, Player defender);

public:
  // Player P1;
  // Player P2;
  std::unordered_map<UID, Player *> Players;

  bool isWild;
  int roundEndCounter;

  BattleHolder(Player *p1, Player *p2, int32_t groupID);
  BattleHolder(Player *p1, Wild com, int32_t groupID);
  ~BattleHolder() = default;

  // String generators
  std::string generateBattleSummary();
  std::string generateMoveSummary(UID);
  std::string generateSwapReport(UID);

  void HandlePlayerChoice(UID uid, int moveNo, bool swap);
  void HandleRoundStart();
  void HandleRoundEnd();
  void SwapPokemon(UID uid, int index);
  void sendSwapReport(UID uid);
};

inline std::unordered_map<UID, BattleHolder *> allBattles;

void registerBattle(UID, BattleHolder *);
void deregisterBattle(BattleHolder *);
bool isBattleActive(UID);

BattleHolder *generateBattle(Player *p1, Player *p2, int32_t groupID);
bool isDefeated(Player *player);

#endif
