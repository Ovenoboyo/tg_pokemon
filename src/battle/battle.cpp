#include "pokemon/battle/baseBattle.h"
#include "pokemon/battle/battle.h"
#include "pokemon/user/player.h"

bool isBattleActive(UID uid) {
    std::unordered_map<UID, BaseBattle *>::iterator it = allBattles.find(uid);
    return it != allBattles.end();
}

void registerBattle(UID p1, BaseBattle *battle) {
    if (!isBattleActive(p1)) {
        allBattles.insert({p1, battle});
    }
}

void deregisterBattle(BaseBattle *battle, std::vector<UID> uidList) {
    for (auto u : uidList) {
        std::unordered_map<UID, BaseBattle *>::iterator it = allBattles.find(u);
        if (it != allBattles.end()) {
            allBattles.erase(it);
        }
    }
    delete battle;
}