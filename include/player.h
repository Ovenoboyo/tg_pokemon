#include <string>
#include "pokemon.h"
#include "box.h"
#include "moves.h"

#ifndef Player_H
#define Player_H

enum Genders {MALE,FEMALE};

class Bag{
    private:
    // TODO: Bag class
};

class Player{
    private:
        // Unique ID
        std::string UID;

        // Name of player
        std::string Name;
        
        // Gender of player
        Genders Gender;

        // Team of pokemons
        Pokemon Team[6];

        // Pokemon box storage
        Box Boxes[10];

        // Bag of items
        Bag Bag;

        // Count of pokemons in team
        int teamCount;

        //Moveset
        Move moveset[4];

    public:
        Player(std::string, std::string, enum Genders);
        Player() = default;

        bool addPokemonInTeam(Pokemon);

        Pokemon * getTeam();
        Box getBox(int);

        std::string getUID();
    };

#endif