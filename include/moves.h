#ifndef MOVES_H
#define MOVES_H

#include<string>
#include "global.h"

class Move {
    private:
        std::string name;
        ElementType type;

        int Damage;
        int Accuracy;

    public:
        int PP;
        bool isEmpty;

        Move(std::string, ElementType, int, int, int);
        Move() = default;

        // Getters
        std::string GetName();
        ElementType GetType();
        int GetDamage();
        int GetAccuracy();
};


#endif