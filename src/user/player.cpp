#include "pokemon/user/player.h"

#include "pokemon/pokemon.h" // for Pokemon

Player::Player(UID uid, std::string name, enum Genders gender, std::vector<std::shared_ptr<Pokemon>> team) {
    this->Uid = uid;
    this->Name = name;
    this->Gender = gender;
    this->FntCount = 0;
    this->isEmpty = false;
    for (const auto &e : team) {
        this->Team.push_back(std::make_shared<Pokemon>(*e));
    }
};

Player::Player() { this->isEmpty = true; }