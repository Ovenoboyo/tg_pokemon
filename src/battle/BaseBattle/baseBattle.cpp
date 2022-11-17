#include "pokemon/battle/baseBattle.h"

#include <iostream> // for std
#include <random>   // for mt19937, random_device, uniform_int_dist...
#include <vector>   // for vector

#include "pokemon/global.h" // for ElementType

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

BaseBattle::BaseBattle(std::shared_ptr<Player> p1, int32_t groupID) {
    this->player1 = p1;
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

bool isDefeated(std::shared_ptr<Player> player) {
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
    return int((((((((((2 * holder.AttackerLevel) / 5 + 2) * holder.AttackStat *
                      holder.power) /
                     holder.DefenceStat) /
                    50) +
                   2) *
                  holder.attackModifier) *
                 holder.typeModifier) *
                random) /
               255);
}
