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

void Move::SetName(std::string name) {
    this->name = name;
}

ElementType Move::GetType() {
        return this->type;
}

void Move::SetType(ElementType type) {
        this->type = type;
}

int Move::GetPP() {
        return this->PP;
}

void Move::SetPP(int PP) {
        this->PP = PP;
}

int Move::GetDamage() {
        return this->Damage;
}

void Move::SetDamage(int Damage) {
        this->Damage = Damage;
}

int Move::GetAccuracy() {
        return this->Accuracy;
}

void Move::SetAccuracy(int Accuracy) {
        this->Accuracy = Accuracy;
}