#include "pokemon/user/player.h"

#include "pokemon/pokemon.h" // for Pokemon

Player::Player(UID uid, std::string name, enum Genders gender, std::vector<Pokemon::Ptr> team) {
    this->Uid = uid;
    this->Name = name;
    this->Gender = gender;
    this->FntCount = 0;
    this->isEmpty = false;
    this->hasPlayed = true;
    this->isSwapping = false;
    for (const auto &e : team) {
        this->Team.push_back(std::make_shared<Pokemon>(*e));
    }
};

Player::Player() { this->isEmpty = true; }