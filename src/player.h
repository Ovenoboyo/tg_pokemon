#include<string>
#include<pokemon.h>

enum Genders {MALE,FEMALE};


class Player{
    private:
    std::string Name;
    int teamCount;
    int boxCount;
    
    // TODO: Name object
    Genders Gender; 
    Pokemon Team[6];
    Box Boxes[10];
    Bag Bag;

    public:
    Player(std::string,enum Genders);
    bool addTeam(Pokemon);
    bool addBox(Pokemon);
    Pokemon * getTeam();
    Box getBox(int);
};

class Bag{
    private:
    // TODO: Bag class
};

class Box{
    private:
    Pokemon pokemons[5][6];

};