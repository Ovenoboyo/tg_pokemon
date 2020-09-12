#include "battleHolder.h"
#include "bot/bot.h"
#include "bot/events/events.h"
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

BattleHolder::BattleHolder(Player *p1, Player *p2, int32_t groupID) {
  this->isWild = false;
  this->roundEndCounter = 2;

  this->Players.insert(std::pair<UID, Player *>(p1->Uid, p1));
  this->Players.insert(std::pair<UID, Player *>(p2->Uid, p2));

  this->botReportID = groupID;

  if (groupID != -1) {
    this->isGroup = true;
  } else {
    this->isGroup = false;
  }

  this->HandleRoundStart();
}

float getAttackModifier(ElementType pkType[], ElementType akType) {
  for (int i = 0; i < 2; i++) {
    if (pkType[i] == akType) {
      return 1.5f;
    }
  }
  return 1;
}

BattleHolder::BattleHolder(Player *p1, Wild com, int32_t groupID) {
  this->Players.insert(std::pair<UID, Player *>(p1->Uid, p1));
  this->Com = com;
  this->isWild = true;

  this->botReportID = groupID;

  if (groupID != -1) {
    this->isGroup = false;
  } else {
    this->isGroup = true;
  }
}

int BattleHolder::calculateDamage(Player attacker, Player defender) {
  auto move = this->playedMove[attacker.Uid];

  if (!move.isEmpty) {

    int Attackerlevel = attacker.Team[0]->Level;
    int DefenderLevel = defender.Team[0]->Level;

    int attackStat = getStat(
        attacker.Team[0]->baseStats.Attack, attacker.Team[0]->IVStats.Attack,
        attacker.Team[0]->EVStats.Attack, Attackerlevel, false);
    int power = move.GetDamage();

    int defenceStat = getStat(
        defender.Team[0]->baseStats.Attack, defender.Team[0]->IVStats.Attack,
        defender.Team[0]->EVStats.Attack, Attackerlevel, false);

    float attackModifier =
        getAttackModifier(defender.Team[0]->type, move.GetType());

    // TODO: Make effectiveness chart

    float typeModifier = 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(217, 255);

    int random = distr(gen);

    // https://www.math.miami.edu/~jam/azure/compendium/battdam.htm
    return int((((((((((2 * Attackerlevel) / 5 + 2) * attackStat * power) /
                     defenceStat) /
                    50) +
                   2) *
                  attackModifier) *
                 typeModifier) *
                random) /
               255);
  }
  return 0;
}

void BattleHolder::ApplyMoves() {
  for (auto m : this->playedMove) {
    UID uid = m.first;

    // Set attacker and defender
    auto attacker = (this->Players[uid]);
    if (!attacker->Team[0]->isFNT) {
      for (auto p : this->Players) {
        if (p.first != uid) {
          auto defender = (p.second);

          // Get damage dealt
          int damage = calculateDamage(*attacker, *defender);

          // Apply damage onto defender pokemon
          defender->Team[0]->Health -= damage;

          // Check if pokemon fainted
          if (defender->Team[0]->Health <= 0) {
            defender->Team[0]->isFNT = true;
            defender->FntCount += 1;

            // Ask user to swap pokemon if fainted and not defeated
            if (!isDefeated(defender)) {
              this->sendSwapReport(defender->Uid);
              defender->isSwapping = true;
            }
          }
          break;
        }
      }
    } else {
      if (!isDefeated(attacker)) {
        this->sendSwapReport(attacker->Uid);
        attacker->isSwapping = true;
      }
    }
  }
  this->playedMove.clear();
}

void BattleHolder::HandleRoundStart() {
  if (this->isGroup) {
    sendMessages(bot, this->botReportID, this->generateBattleSummary());
  }
  for (auto p : this->Players) {
    if (this->isGroup) {
      sendMessages(bot, this->botReportID, this->generateMoveSummary(p.first));
    } else {
      sendMessages(bot, p.first, this->generateBattleSummary());
      sendMessages(bot, p.first, this->generateMoveSummary(p.first));
    }
  }
}

void BattleHolder::HandleRoundEnd() {
  bool isEnd = false;
  // TODO: Generate who played what and damage dealt summary
  for (auto p : this->Players) {
    if (isDefeated(p.second)) {
      isEnd = true;
      if (this->isGroup) {
        sendMessages(bot, this->botReportID,
                     std::to_string(p.first) + " Lost :''(");
        break;
      }
      sendMessages(bot, p.first, std::to_string(p.first) + " Lost :''(");
    }
  }
  if (isEnd) {
    deregisterBattle(this);
    return;
  }
  this->HandleRoundStart();
}

std::string BattleHolder::generateBattleSummary() {
  std::string ret = "";
  for (auto p : this->Players) {
    ret.append("pokemon health: " + std::to_string(p.second->Team[0]->Health) +
               "\n");
  }
  return ret;
}

std::string BattleHolder::generateMoveSummary(UID uid) {
  auto moveset = this->Players[uid]->Team[0]->Moveset;
  return "Move 1: " + moveset.move1.GetName() + "\n" +
         "Move 2: " + moveset.move2.GetName() + "\n" +
         "Move 3: " + moveset.move3.GetName() + "\n" +
         "Move 4: " + moveset.move4.GetName();
}

Move BattleHolder::getMoveFromIndex(UID uid, int moveNo) {
  switch (moveNo) {
  case 1:
    return this->Players[uid]->Team[0]->Moveset.move1;
  case 2:
    return this->Players[uid]->Team[0]->Moveset.move2;
  case 3:
    return this->Players[uid]->Team[0]->Moveset.move3;
  case 4:
    return this->Players[uid]->Team[0]->Moveset.move4;
  }
  return Move();
}

void BattleHolder::SwapPokemon(UID uid, int index) {
  // TODO: implement swapping
  std::swap(this->Players[uid]->Team[0], this->Players[uid]->Team[index]);
}

std::string BattleHolder::generateSwapReport(UID uid) {
  // TODO: generate swap report
  return "keks";
}

void BattleHolder::sendSwapReport(UID uid) {
  if (this->Players[uid]->Team.size() > 1) {
    sendMessages(bot, uid, this->generateSwapReport(uid));
  }
}

void BattleHolder::HandlePlayerChoice(UID uid, int index, bool swap) {
  std::unordered_map<UID, Player *>::iterator it = this->Players.find(uid);
  if (it != this->Players.end()) {
    auto player = this->Players[uid];

    // Check if user is swapping or playing a move
    if (swap || player->isSwapping) {
      this->SwapPokemon(uid, index);
      player->isSwapping = false;

      // Make getMoveFromIndex return empty move
      this->playedMove.insert(
          std::pair<UID, Move>(uid, getMoveFromIndex(uid, 69)));
    } else {
      auto move = getMoveFromIndex(uid, index);
      if (!move.isEmpty) {
        this->playedMove.insert(std::pair<UID, Move>(uid, move));
      } else {
        // Can't play this move
        return;
      }
    }

    this->roundEndCounter--;

    // Check if round ended
    if (this->roundEndCounter == 0) {
      this->roundEndCounter = 2;
      this->ApplyMoves();
      this->HandleRoundEnd();
    } else {
      sendMessages(bot, (this->isGroup) ? this->botReportID : uid,
                   "Waiting for other player...");
    }
  } else {
    // TODO: Already played move
  }
}

BattleHolder *generateBattle(Player *p1, Player *p2, int32_t groupID) {
  return new BattleHolder(p1, p2, groupID);
}

bool isDefeated(Player *player) {
  int maxFnt = player->Team.size();
  if (player->FntCount == maxFnt) {
    return true;
  }
  return false;
}

bool isBattleActive(UID uid) {
  std::unordered_map<UID, BattleHolder *>::iterator it = allBattles.find(uid);
  return it != allBattles.end();
}

void registerBattle(UID p1, BattleHolder *battle) {
  if (!isBattleActive(p1)) {
    allBattles.insert({p1, battle});
  }
}

void deregisterBattle(BattleHolder *battle) {
  for (auto p : battle->Players) {
    std::unordered_map<UID, BattleHolder *>::iterator it =
        allBattles.find(p.first);
    if (it != allBattles.end()) {
      allBattles.erase(it);
    }
  }
  delete battle;
}
