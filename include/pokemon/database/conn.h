#ifndef CONN_H
#define CONN_H

#include <memory>                 // for shared_ptr
#include <string>                 // for allocator, operator+, char_traits
#include <vector>                 // for vector

#include "pokemon/global.h"       // for getEnvVar, ElementType
#include "pokemon/pokemon.h"      // for Pokemon (ptr only), Stats
#include "pokemon/user/player.h"  // for UID, Genders, Player (ptr only)

class Move;

namespace pqxx {
class connection;
class nontransaction;
class row;
} // namespace pqxx

struct starterHolder {
    std::string name;
    int pokedex_no;
};

const std::string connString =
    "user=" + getEnvVar("username") + " password=" + getEnvVar("password") +
    " host=" + getEnvVar("hostname") + " port=" + getEnvVar("hostport") +
    " dbname=" + getEnvVar("databasename");

class PGConn {
  private:
    pqxx::connection *conn;

  public:
    // Moves
    std::vector<Move *> getMoves(std::string pokemonID,
                                 pqxx::nontransaction &N);
    std::vector<int> getMoveSetByLevel(int pokedexNo, int level);
    std::string insertMovesQuery(std::vector<int> moves, std::string pokemonID);

    // Players
    std::shared_ptr<Player> FetchPlayer(UID uid);
    UID isPlayerRegistered(std::string username);
    bool isPlayerRegistered(UID uid);

    // Pokemon
    std::shared_ptr<Pokemon> FetchUserokemon(std::string pokemonID, pqxx::nontransaction &N);
    std::shared_ptr<Pokemon> GetWildPokemon(int route_no);

    // Starters
    std::vector<starterHolder> getStarters();
    void registerStarter(UID userID, std::string username, int pokedexNo,
                         Genders gender);

    PGConn();
};

Stats parseStats(pqxx::row row);
std::vector<ElementType> parseElements(pqxx::row row);

inline PGConn *dbConn;

#endif
