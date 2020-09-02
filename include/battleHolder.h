#ifndef BATTLEHOLDER_H
#define BATTLEHOLDER_H

#include "player.h"
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "pokemon.h"
#include "wild.h"
#include "player.h"

class BattleHolder {
    private:
        Wild Com;
        std::map<UID, Pokemon*> activePokemon;

    public:
        Player P1;
        Player P2;

        UID whosMove;

        bool isWild;

        BattleHolder(Player*, Player*);
        BattleHolder(Player, Wild);
        ~BattleHolder() = default;

        UID FirstMove();

        // String generators
        std::string getBattleSummary();

};

inline std::map<UID, BattleHolder*> allBattles;

bool registerBattle(UID, BattleHolder*);
bool deregisterBattle(UID);
bool isBattleActive(UID);

BattleHolder *generateBattle(Player *p1, Player *p2);

#endif