#ifndef Player_H
#define Player_H

#include <string>
#include "pokemon.h"
#include "box.h"
#include "moves.h"

typedef std::string UID;

enum Genders {MALE,FEMALE};

class Bag{
    private:
    // TODO: Bag class
};

class Player{
    public:
        // Unique ID
        UID Uid;

        // Name of player
        std::string Name;
        
        // Gender of player
        Genders Gender;

        // Team of pokemons
        Pokemon* Team[6];

        // Bag of items
        Bag bag;

        // Count of pokemons in team
        int teamCount;

        Player(UID, std::string, enum Genders);
        Player() = default;

        bool addPokemonInTeam(Pokemon*);
    };

#endif
