#include "pokemon/user/player.h"

#include "pokemon/pokemon.h" // for Pokemon
#include "pokemon/database/conn.h"

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

Player::Player(bool isWild) {
    this->Uid = BOT_ID;
    auto pokemon = dbConn->GetWildPokemon(1);
    this->Team.push_back(std::make_shared<Pokemon>(*pokemon));
    this->isWild = true;
}

Player::Player() { this->isEmpty = true; }