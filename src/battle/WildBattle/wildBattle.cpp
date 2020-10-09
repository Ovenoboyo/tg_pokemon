#include "pokemon/battle/wildBattle.h"

#include "pokemon/battle/baseBattle.h"  // for BaseBattle

WildBattle::WildBattle(std::list<Player::Ptr> players, int32_t groupID) : BaseBattle(players, groupID) {}