#ifndef BATTLEHOLDER_H
#define BATTLEHOLDER_H

#include "player.h"
#include <map>
#include <string>
#include <list>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "pokemon.h"
#include "wild.h"
#include "player.h"

class BattleHolder {
    private:
        Wild Com;
        std::map<UID, Move> playedMove;

        std::list<int32_t> botReportID;

        Move getMoveFromIndex(UID, int);

        void ApplyMoves();

        int calculateDamage(Player attacker, Player defender);

    public:
        // Player P1;
        // Player P2;
        std::map<UID, Player> Players;

        bool isWild;
        int roundEndCounter;

        BattleHolder(Player* p1, Player* p2, std::list<int32_t> chatIDs);
        BattleHolder(Player* p1, Wild com, std::list<int32_t> chatIDs);
        ~BattleHolder() = default;

        // String generators
        std::string generateBattleSummary();
        std::string generateMoveSummary(UID);

        void HandlePlayerChoice(UID uid, int moveNo);

};

inline std::map<UID, BattleHolder*> allBattles;

bool registerBattle(UID, BattleHolder*);
bool deregisterBattle(UID);
bool isBattleActive(UID);

BattleHolder *generateBattle(Player *p1, Player *p2, std::list<int32_t>);

#endif
