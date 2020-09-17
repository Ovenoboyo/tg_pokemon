#include "pokemon/battle/wildBattle.h"

#include <stddef.h>      // for NULL
#include <unordered_map> // for unordered_map
#include <utility>       // for pair
#include <vector>        // for vector

#include "pokemon/battle/baseBattle.h" // for BaseBattle
#include "pokemon/bot/bot.h"           // for bot
#include "pokemon/bot/events/events.h" // for sendMessages
#include "pokemon/pokemon.h"           // for Pokemon
#include "pokemon/database/dbpokemon.h"

class Move;

WildBattle::WildBattle(Player *p1, int32_t groupID)
    : BaseBattle(p1, groupID) {
    
    this->com = new Wild(GetWildPokemon(69));
}

Move *WildBattle::getMoveFromIndex(Player player, int moveNo) {
    if (moveNo > 4 || moveNo < 0) {
        return NULL;
    } else {
        return player.Team.at(0)->Moveset.at(moveNo);
    }
}

DamageCalcHolder WildBattle::getStats(Pokemon attacker, Pokemon defender, Move move) {
    return DamageCalcHolder{
        attacker.Level,
        getStat(attacker.baseStats.Attack,
                attacker.IVStats.Attack,
                attacker.EVStats.Attack, attacker.Level, false),
        move.GetDamage(),

        defender.Level,
        
        getStat(defender.baseStats.Attack,
                defender.IVStats.Attack,
                defender.EVStats.Attack, attacker.Level, false),

        getAttackModifier(defender.type, move.GetType()),
        1,
    };
}

Pokemon *WildBattle::getActivePokemon(bool isPlayer) {
    return (isPlayer) ? this->player1->Team.at(0) : this->com->pokemon;
}

void WildBattle::ApplyMoves() {
    for (auto m : this->playedMove) {
        UID uid = m.first;

        // Set attacker and defender
        auto attacker = getActivePokemon((uid == BOT_ID));
        auto defender = getActivePokemon((uid != BOT_ID));
        if (!attacker->isFNT) {

            // Get damage dealt
            int damage = calculateDamage(getStats(*attacker, *defender, *m.second));

            // Apply damage onto defender pokemon
            defender->Health -= damage;

            // Check if pokemon fainted
            if (defender->Health <= 0) {
                defender->isFNT = true;

                if (uid == BOT_ID) {
                    this->playedMove.clear();
                    return;
                } else {
                    this->player1->FntCount += 1;
                    if (!this->isDefeated(this->player1)) {
                        this->sendSwapReport(this->player1->Uid);
                        this->player1->isSwapping = true;
                    }
                }
            }
        } else {
            if (uid == BOT_ID) {
                this->playedMove.clear();
                return; 
            } else {
                if (!this->isDefeated(this->player1)) {
                    this->sendSwapReport(this->player1->Uid);
                    this->player1->isSwapping = true;
                }
            }
        }
    }
    this->playedMove.clear();
}

void WildBattle::sendSwapReport(UID uid) {
    auto player = this->player1;
    if (player->Team.size() > 1) {
        sendMessages(*bot, uid, this->generateSwapSummary(*player));
    }
}