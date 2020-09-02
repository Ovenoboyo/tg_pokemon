#include "battleHolder.h"
#include <iostream>
#include <time.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/asio.hpp>
#include <string>
#include <map>


BattleHolder::BattleHolder(Player *p1, Player *p2) {
    this->P1 = *p1;
    this->P2 = *p2;
    this->isWild = false;

    for(int i = 0; i < 2; i++) {
        std::string uid = (i == 0) ? (p1->Uid) : (p2->Uid);
        Pokemon team = (i == 0) ? (p2->Team[0]) : (p2->Team[0]);

        this->activePokemon.insert({uid, &team});
    }
}

BattleHolder::BattleHolder(Player p1, Wild com) {
    this->P1 = p1;
    this->Com = com;
    this->isWild = true;
}

UID BattleHolder::FirstMove() {
    srand((unsigned int)time(NULL));
    return (std::rand() % 2) ? (this->P1.Uid) : (this->P2.Uid);
}

BattleHolder *generateBattle(Player *p1, Player *p2) {
    return new BattleHolder(p1, p2);
}

bool isBattleActive(UID uid) {
    std::map<UID, BattleHolder*>::iterator it = allBattles.find(uid);
    return it != allBattles.end();
}

bool registerBattle(UID p1, BattleHolder *battle) {
    if (!isBattleActive(p1)) {
        allBattles.insert({p1, battle});
        return true;
    }
    return false;
}

bool deregisterBattle(UID uid) {
    std::map<UID, BattleHolder*>::iterator it = allBattles.find(uid);
    if (it != allBattles.end()) {
        allBattles[uid]->~BattleHolder();
        allBattles.erase(it);
        return true;
    }
    return false;
}