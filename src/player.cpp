#include <algorithm>
#include "player.h"

Player::Player(UID uid, std::string name, enum Genders gender, Pokemon **team) {
  this->Uid = uid;
  this->Name = name;
  this->Gender = gender;
  this->teamCount = 0;
  std::copy(team, team + 6, this->Team);
};