#include<player.h>

Player::Player(std::string name,enum Genders gender){
    Player::Name = name;
    Player::Gender = gender;
    Player::teamCount = 0;
};

bool Player::addTeam(Pokemon p){
    if (Player::teamCount<6){
        Player::Team[Player::teamCount] = p;
        Player::teamCount+=1;
        return true;
    }
    return false;
}

bool Player::addBox(Pokemon p){
    if (Player::boxCount<6){
        Player::Team[Player::boxCount] = p;
        Player::boxCount+=1;
        return true;
    }
    return false;
}

Pokemon * Player::getTeam(){
    return Player::Team;
}

Box Player::getBox(int i){
    return Player::Boxes[i];
}
