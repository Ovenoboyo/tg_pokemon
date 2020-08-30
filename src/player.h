#include<string>
#include<pokemon.h>

enum Genders {MALE,FEMALE};


class Player{
    private:
    std::string Name;
    
    // TODO: Name object
    Genders Gender; 
    Pokemon Team[6];
    Box Boxes[10];
    Bag Bag;

    public:
    Player(std::string,enum Genders);

};

class Bag{
    private:
    // TODO: Bag class
};

class Box{
    private:
    Pokemon pokemons[5][6];

};