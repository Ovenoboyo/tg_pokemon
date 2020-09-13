#include "pokemon/battle/dualBattle.h"

#include <unordered_map> // for unordered_map
#include <utility>       // for pair
#include <vector>        // for vector

#include "pokemon/battle/baseBattle.h" // for BaseBattle
#include "pokemon/bot/bot.h"           // for bot
#include "pokemon/bot/events/events.h" // for sendMessages
#include "pokemon/pokemon.h"           // for Pokemon, MoveSet

DualBattle::DualBattle(Player *p1, Player *p2, int32_t groupID)
    : BaseBattle(p1, groupID) {
  this->player2 = p2;
  this->HandleRoundStart();
}

Player *DualBattle::GetOtherPlayer(UID uid) {
  return (uid == this->player1->Uid) ? this->player1 : this->player2;
}

Player *DualBattle::GetPlayer(UID uid) {
  return (uid == this->player1->Uid) ? this->player2 : this->player1;
}

Move DualBattle::getMoveFromIndex(Player player, int moveNo) {
  switch (moveNo) {
  case 1:
    return player.Team[0]->Moveset.move1;
  case 2:
    return player.Team[0]->Moveset.move2;
  case 3:
    return player.Team[0]->Moveset.move3;
  case 4:
    return player.Team[0]->Moveset.move4;
  }
  return Move();
}

void DualBattle::ApplyMoves() {
  for (auto m : this->playedMove) {
    UID uid = m.first;

    // Set attacker and defender
    auto attacker = this->GetPlayer(uid);
    if (!attacker->Team[0]->isFNT) {
      auto defender = this->GetOtherPlayer(uid);

      // Get damage dealt
      int damage = calculateDamage(*attacker, *defender);

      // Apply damage onto defender pokemon
      defender->Team[0]->Health -= damage;

      // Check if pokemon fainted
      if (defender->Team[0]->Health <= 0) {
        defender->Team[0]->isFNT = true;
        defender->FntCount += 1;

        // Ask user to swap pokemon if fainted and not defeated
        if (!this->isDefeated(defender)) {
          this->sendSwapReport(defender->Uid);
          defender->isSwapping = true;
        }
      }
    } else {
      if (!this->isDefeated(attacker)) {
        this->sendSwapReport(attacker->Uid);
        attacker->isSwapping = true;
      }
    }
  }
  this->playedMove.clear();
}

void DualBattle::sendSwapReport(UID uid) {
  auto player = this->GetPlayer(uid);
  if (player->Team.size() > 1) {
    sendMessages(bot, uid, this->generateSwapSummary(*player));
  }
}