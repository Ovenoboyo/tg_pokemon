#ifndef Player_H
#define Player_H

#include <memory>   // for shared_ptr
#include <stdint.h> // for int32_t
#include <string>   // for string
#include <vector>   // for vector

class Pokemon;

const int32_t INVALID_ID = -1;
const int32_t BOT_ID = -2;

typedef int32_t UID;
enum Genders { MALE, FEMALE };

class Player {
  public:
    /**
     * @brief Unique ID for player. Usually User-ID provided by telegram
     *
     */
    UID Uid;

    /**
     * @brief Name of player
     *
     */
    std::string Name;

    /**
     * @brief Gender of Player
     *
     */
    Genders Gender;

    /**
     * @brief Team of 6 (MAX) Pokemons
     *
     */
    std::vector<std::shared_ptr<Pokemon>> Team;

    /**
     * @brief Bool to check if next move corresponds to swapping
     *
     */
    bool isSwapping;

    /**
     * @brief Counter to keep track of fainted pokemons
     *
     */
    int FntCount;

    bool isEmpty;

    /**
     * @brief Construct a new Player object
     *
     * @param uid UID of player
     * @param name Name of player
     * @param gender Gender of player
     * @param team Vector with Pokemon objects
     */
    Player(UID uid, std::string name, enum Genders gender, std::vector<std::shared_ptr<Pokemon>> team);

    /**
     * @brief Construct a new Player object
     *
     */
    Player();
};

#endif
