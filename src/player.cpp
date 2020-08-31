#include "player.h"

Player::Player(UID uid, std::string name, enum Genders gender) {
    this->Uid = uid;
    this->Name = name;
    this->Gender = gender;
    this->teamCount = 0;
};

bool Player::addPokemonInTeam(Pokemon p){
    if (this->teamCount<6){
        this->Team[Player::teamCount] = p;
        this->teamCount+=1;
        return true;
    }
    return false;
}

Box Player::getBox(int i) {
    return this->Boxes[i];
}

Pokemon *Player::getTeam(){
    return this->Team;
}

UID Player::getUID() {
    return this->Uid;
}
