#include "pokemon/battle/dualBattle.h"

#include <list>                         // for list

#include "pokemon/battle/baseBattle.h"  // for BaseBattle

DualBattle::DualBattle(std::list<Player::Ptr> players, int32_t groupID)
    : BaseBattle(players, groupID) {
}