#include "moves.h"

Move::Move(const std::string name, ElementType type, int damage, int accuracy,
           int pp) {
  this->name = name;
  this->type = type;
  this->PP = pp;
  this->Damage = damage;
  this->Accuracy = accuracy;
  this->isEmpty = false;
}

Move::Move() {
  this->name = "";
  this->type = NIL;
  this->PP = 0;
  this->Damage = 0;
  this->Accuracy = 0;
  this->isEmpty = true;
}

std::string Move::GetName() { return this->name; }

ElementType Move::GetType() { return this->type; }

int Move::GetDamage() { return this->Damage; }

int Move::GetAccuracy() { return this->Accuracy; }