#include "player.h"
#include <map>

class BattleHolder {
    private:
        Player Players[2];
        std::map<std::string, Pokemon*> Pokemons;
        std::map<std::string, Pokemon> activePokemon;

    public:
        BattleHolder(Player, Player);
        Player FirstMove();
};