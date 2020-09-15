#include "pokemon/battle/baseBattle.h"

#include <iostream>      // for std
#include <random>        // for mt19937, random_device, uniform_int_dis...
#include <stddef.h>      // for NULL
#include <stdexcept>     // for runtime_error
#include <unordered_map> // for unordered_map
#include <vector>        // for vector

#include "pokemon/global.h"  // for ElementType
#include "pokemon/pokemon.h" // for Pokemon, Stats, getStat

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

BaseBattle::BaseBattle(Player *p1, int32_t groupID) {
    this->player1 = p1;

    ChatInfo chatInfo(groupID);
}

Move BaseBattle::getMoveFromIndex(Player player, int moveNo) {
    throw std::runtime_error("Not Implemented");
}

float getAttackModifier(std::vector<ElementType> pkType, ElementType akType) {
    for (int i = 0; i < 2; i++) {
        if (pkType.at(i) == akType) {
            return 1.5f;
        }
    }
    return 1;
}

void BaseBattle::sendSwapReport(UID uid) {
    throw std::runtime_error("Not Implemented");
}

bool BaseBattle::isDefeated(Player *player) {
    int maxFnt = player->Team.size();
    if (player->FntCount == maxFnt) {
        return true;
    }
    return false;
}

int BaseBattle::calculateDamage(Player attacker, Player defender) {
    auto move = this->playedMove.at(attacker.Uid);

    if (move != NULL) {

        int Attackerlevel = attacker.Team.at(0)->Level;
        int DefenderLevel = defender.Team.at(0)->Level;

        int attackStat =
            getStat(attacker.Team.at(0)->baseStats.Attack,
                    attacker.Team.at(0)->IVStats.Attack,
                    attacker.Team.at(0)->EVStats.Attack, Attackerlevel, false);
        int power = move->GetDamage();

        int defenceStat =
            getStat(defender.Team.at(0)->baseStats.Attack,
                    defender.Team.at(0)->IVStats.Attack,
                    defender.Team.at(0)->EVStats.Attack, Attackerlevel, false);

        float attackModifier =
            getAttackModifier(defender.Team.at(0)->type, move->GetType());

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
