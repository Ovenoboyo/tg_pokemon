#include<string>
#include<pokemon.h>

enum Gender {MALE,FEMALE};


class Player{
    private:
    std::string Name;
    // TODO: Name object
    Gender gender; 
    Pokemon team[6];
    Box boxes[10];
    Bag bag;

};

class Bag{
    private:
    // TODO: Bag class
};

class Box{
    private:
    Pokemon pokemons[5][6];

};