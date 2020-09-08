#include "battleHolder.h"
#include <iostream>
#include <time.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/asio.hpp>
#include <string>
#include <map>
#include <random>

using namespace std;

BattleHolder::BattleHolder(Player *p1, Player *p2, std::list<int32_t> chatIDs) {
    this->isWild = false;
    this->roundEndCounter = 2;

    this->Players.insert(std::pair<UID, Player>(p1->Uid, *p1));
    this->Players.insert(std::pair<UID, Player>(p2->Uid, *p2));

    this->botReportID.merge(chatIDs);

    for(int i = 0; i < 2; i++) {
        std::string uid = (i == 0) ? (p1->Uid) : (p2->Uid);
        Pokemon *team = (i == 0) ? (p2->Team[0]) : (p2->Team[0]);
    }
}

int getStats(int base, int iv, int ev, int level, bool isHP) {
    if (!isHP) {
        // Stats = ([(Base + IV)*2 + EV/4] * level)/100 + 5
        return int(((((base + iv) * 2) + (ev/4)) * level)/100) + 5;
    } else {
        //TODO: HP Stats logic
        return 0;
    }
}

float getAttackModifier(ElementType pkType[], ElementType akType) {
    for (int i = 0; i < 2; i++) {
        if (pkType[i] == akType) {
            return 1.5f;
        }
    }
    return 1;
}

BattleHolder::BattleHolder(Player *p1, Wild com, std::list<int32_t> chatIDs) {
    this->Players.insert(std::pair<UID, Player>(p1->Uid, *p1));
    this->Com = com;
    this->isWild = true;

    this->botReportID.merge(chatIDs);
}

int BattleHolder::calculateDamage(Player attacker, Player defender) {
    int Attackerlevel = attacker.Team[0]->Level;
    int DefenderLevel = defender.Team[0]->Level;

    int attackStat = getStats(attacker.Team[0]->baseStats.Attack, attacker.Team[0]->IVStats.Attack, attacker.Team[0]->EVStats.Attack, Attackerlevel, false);
    int power = this->playedMove[attacker.Uid].GetDamage();

    int defenceStat = getStats(defender.Team[0]->baseStats.Attack, defender.Team[0]->IVStats.Attack, defender.Team[0]->EVStats.Attack, Attackerlevel, false);

    float attackModifier = getAttackModifier(defender.Team[0]->type, this->playedMove[attacker.Uid].GetType());

    // TODO: Make effectiveness chart

    float typeModifier = 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(217, 255);

    int random = distr(gen);

    // https://www.math.miami.edu/~jam/azure/compendium/battdam.htm
    return int((((((((((2 * Attackerlevel)/5 + 2) * attackStat * power) / defenceStat) / 50) + 2) * attackModifier) * typeModifier) * random) / 255);
}

void BattleHolder::ApplyMoves() {
    for (auto m : this->playedMove) {
        UID uid = m.first;
        auto attacker = &(this->Players[uid]);
        for (auto p : this->Players) {
            if (p.first != uid) {
                auto defender = &(p.second);
                int damage = calculateDamage(*attacker, *defender);

                defender->Team[0]->Health -= damage;
                break;
            }
        }
    }
}

std::string BattleHolder::generateBattleSummary() {
    std::string ret = "";
    for (auto p : this->Players) {
        ret.append("pokemon health: " + std::to_string(p.second.Team[0]->Health) + "\n");
    }
    return ret;
}

std::string BattleHolder::generateMoveSummary(UID uid) {
    auto moveset = this->Players[uid].Team[0]->Moveset;
    return "Move 1: " + moveset.move1.GetName() + "\n"
         + "Move 2: " + moveset.move2.GetName() + "\n"
         + "Move 3: " + moveset.move3.GetName() + "\n"
         + "Move 4: " + moveset.move4.GetName();
}

Move BattleHolder::getMoveFromIndex(UID uid, int moveNo) {
    switch (moveNo)
    {
    case 1:
        return this->Players[uid].Team[0]->Moveset.move1;
    case 2:
        return this->Players[uid].Team[0]->Moveset.move2;
    case 3:
        return this->Players[uid].Team[0]->Moveset.move3;
    case 4:
        return this->Players[uid].Team[0]->Moveset.move4;
    }
    return Move();
}

void BattleHolder::HandlePlayerChoice(UID uid, int moveNo) {
    this->playedMove.insert(std::pair<UID, Move>(uid, getMoveFromIndex(uid, moveNo)));
    this->roundEndCounter--;

    if (this->roundEndCounter == 0) {
        this->roundEndCounter = 2;
        this->ApplyMoves();
        std::cout << std::endl << this->generateBattleSummary();
    }
}

BattleHolder *generateBattle(Player *p1, Player *p2, std::list<int32_t> chatIDs) {
    return new BattleHolder(p1, p2, chatIDs);
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

