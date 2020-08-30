#include "player.h"

Player::Player(std::string uid, std::string name,enum Genders gender) {
    this->UID = uid;
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

std::string Player::getUID() {
    return this->UID;
}
