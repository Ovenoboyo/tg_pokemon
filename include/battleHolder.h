#include "player.h"
#include <map>

class BattleHolder {
    private:
        Player Players[2];
        std::map<UID, Pokemon*> Pokemons;
        std::map<UID, Pokemon> activePokemon;

        std::string whosMove;

    public:
        BattleHolder(Player, Player);

        UID FirstMove();

};