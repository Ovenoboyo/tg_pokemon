#include "pokemon/user/player.h"

#include <algorithm> // for max
#include <iterator>  // for move_iterator, make_move_iterator

class Pokemon;

Player::Player(UID uid, std::string name, enum Genders gender,
               std::vector<Pokemon *> team) {
    this->Uid = uid;
    this->Name = name;
    this->Gender = gender;
    this->FntCount = 0;
    this->Team.insert(this->Team.end(), std::make_move_iterator(team.begin()),
                      std::make_move_iterator(team.end()));
};