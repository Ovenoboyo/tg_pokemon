#ifndef MOVES_H
#define MOVES_H

#include "pokemon/global.h"
#include <string>

class Move {
private:
  int Damage;
  int Accuracy;
  ElementType type;
  std::string name;

public:
  int PP;
  bool isEmpty;

  Move(std::string name, ElementType type, int damage, int accuracy, int pp);
  Move();

  // Getters
  std::string GetName();
  ElementType GetType();
  int GetDamage();
  int GetAccuracy();
};

#endif
