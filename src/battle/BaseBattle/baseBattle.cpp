#include "pokemon/battle/baseBattle.h"

#include <ext/alloc_traits.h>  // for __alloc_traits<>::value_type
#include <stddef.h>            // for NULL
#include <iostream>            // for std
#include <list>                // for list
#include <random>              // for mt19937, random_device, uniform_int_distribution
#include <utility>             // for pair
#include <vector>              // for vector

#include "pokemon/global.h"    // for ElementType
#include "pokemon/moves.h"     // for Move
#include "pokemon/pokemon.h"   // for Pokemon, Stats, getStat

using namespace std;

ChatInfo::ChatInfo(int32_t groupID) {
    if (groupID != -1) {
        this->isGroup = true;
        this->botReportID = groupID;
    } else {
        this->isGroup = false;
        this->botReportID = INVALID_ID;
    }
}

BaseBattle::BaseBattle(std::list<Player::Ptr> players, int32_t groupID) {
    for (auto p : players) {
        this->players[p->Uid] = p;
    }
    this->isEnd = false;
    this->chat = new ChatInfo(groupID);
}

float getAttackModifier(std::vector<ElementType> pkType, ElementType akType) {
    for (int i = 0; i < 2; i++) {
        if (pkType.at(i) == akType) {
            return 1.5f;
        }
    }
    return 1;
}

bool isDefeated(Player::Ptr player) {
    int maxFnt = player->Team.size();
    if (player->FntCount == maxFnt) {
        return true;
    }
    return false;
}

int BaseBattle::calculateDamage(const struct DamageCalcHolder holder) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(217, 255);

    int random = distr(gen);

    // https://www.math.miami.edu/~jam/azure/compendium/battdam.htm
    return int(
        (((((((((2 * holder.AttackerLevel) / 5 + 2) * holder.AttackStat * holder.power) / holder.DefenceStat) / 50) +
            2) *
           holder.attackModifier) *
          holder.typeModifier) *
         random) /
        255);
}

Player::Ptr BaseBattle::GetPlayer(UID uid) {
    if ((this->players.find(uid) != this->players.end())) {
        return this->players[uid];
    }
    return std::make_shared<Player>();
}

Player::Ptr BaseBattle::GetOtherPlayer(UID uid) {
    for (auto p : this->players) {
        if (p.first != uid) {
            return p.second;
        }
    }
    return std::make_shared<Player>();
}

Move *BaseBattle::GetMoveFromIndex(Player player, int moveNo) {
    if (moveNo > 4 || moveNo < 0) {
        return NULL;
    } else {
        return player.Team.at(0)->Moveset.at(moveNo);
    }
}

DamageCalcHolder::Ptr BaseBattle::getStats(Pokemon attacker, Pokemon defender, Move move) {
    return std::make_shared<DamageCalcHolder>(DamageCalcHolder{
        attacker.Level,
        getStat(attacker.baseStats.Attack, attacker.IVStats.Attack, attacker.EVStats.Attack, attacker.Level, false),
        move.GetDamage(),

        defender.Level,

        getStat(defender.baseStats.Attack, defender.IVStats.Attack, defender.EVStats.Attack, attacker.Level, false),

        getAttackModifier(defender.type, move.GetType()),
        1,
    });
}

void BaseBattle::ApplyMoves() {
    for (auto m : this->playedMove) {
        UID uid = m.first;

        // Set attacker and defender
        auto attacker = this->GetPlayer(uid);
        if (!attacker->Team.at(0)->isFNT) {
            auto defender = this->GetOtherPlayer(uid);

            // Get damage dealt
            auto dmg = this->getStats(*attacker->Team.at(0), *defender->Team.at(0), *(m.second));
            int damage = calculateDamage(*dmg);

            // Apply damage onto defender pokemon
            defender->Team.at(0)->Health -= damage;

            // Check if pokemon fainted
            if (defender->Team.at(0)->Health <= 0) {
                defender->Team.at(0)->isFNT = true;
                defender->FntCount += 1;

                // Ask user to swap pokemon if fainted and not defeated
                if (!isDefeated(defender) && !defender->isWild) {
                    defender->isSwapping = true;
                }
            }
        } else {
            if (!isDefeated(attacker) && !attacker->isWild) {
                attacker->isSwapping = true;
            }
        }
    }
    this->playedMove.clear();
}

void BaseBattle::SwapPokemon(UID uid, int index) {
    auto player = this->GetPlayer(uid);
    std::swap(player->Team.at(0), player->Team[index]);
}

void BaseBattle::sendSwapReport(UID uid) {
    auto player = this->GetPlayer(uid);
    if (!player->isWild && player->Team.size() > 1) {
        //sendMessage(*bot, uid, this->GenerateSwapReport());
    }
}