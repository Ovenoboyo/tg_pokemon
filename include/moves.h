#include<string>
#include "global.h"

#ifndef MOVES_H
#define MOVES_H

class Move {
    private:
        std::string name;
        ElementType type;
        int PP;
        int Damage;
        int Accuracy;

    public:
        Move(std::string, ElementType, int, int, int);
        Move() = default;

        // Getters
        std::string GetName();
        ElementType GetType();
        int GetPP();
        int GetDamage();
        int GetAccuracy();
};


#endif