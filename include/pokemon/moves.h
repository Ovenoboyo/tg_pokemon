#ifndef MOVES_H
#define MOVES_H

#include "pokemon/global.h"
#include <string>

class Move {
  private:
    // TODO: Check if move uses Special attack or Normal Attack Stat

    /**
     * @brief Damage / Power of Move
     *
     */
    int Damage;

    /**
     * @brief Accuracy of Move
     *
     */
    int Accuracy;

    /**
     * @brief Type of Move
     *
     */
    ElementType type;

    /**
     * @brief Name of move
     *
     */
    std::string name;

  public:
    /**
     * @brief Power Points of move
     *
     */
    int PP;

    /**
     * @brief True if move is invalid
     *
     */
    bool isEmpty;

    /**
     * @brief Construct a new Move object
     *
     * @param name Name of move
     * @param type Type of move
     * @param damage Damage / Power of Move
     * @param accuracy Accuracy of Move
     * @param pp Power points of move
     */
    Move(std::string name, ElementType type, int damage, int accuracy, int pp);

    /**
     * @brief Construct a new Move object
     *
     */
    Move();

    // Getters

    /**
     * @brief Get the Name object
     *
     * @return std::string name
     */
    std::string GetName();

    /**
     * @brief Get the ElementType object
     *
     * @return ElementType Type
     */
    ElementType GetType();

    /**
     * @brief Get the Damage
     *
     * @return int damage
     */
    int GetDamage();

    /**
     * @brief Get the Accuracy
     *
     * @return int accuracy
     */
    int GetAccuracy();
};

#endif
