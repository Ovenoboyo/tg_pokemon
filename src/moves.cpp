#include "moves.h"

Move::Move(std::string name, ElementType type, int pp, int damage, int accuracy) {
    this->name = name;
    this->type = type;
    this->PP = pp;
    this->Damage = damage;
    this->Accuracy = accuracy;
}

std::string Move::GetName() {
    return this->name;
}

ElementType Move::GetType() {
        return this->type;
}

int Move::GetDamage() {
    return this->Damage;
}

int Move::GetAccuracy() {
    return this->Accuracy;
}