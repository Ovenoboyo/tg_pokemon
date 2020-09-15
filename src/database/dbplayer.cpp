#include "pokemon/database/dbplayer.h"

#include <algorithm>               // for max
#include <fmt/core.h>              // for format
#include <pokemon/database/conn.h> // for PGConn, dbConn
#include <pqxx/pqxx>
#include <stdexcept> // for runtime_error
#include <string>    // for string, allocator, to_string
#include <vector>    // for vector

#include "pokemon/database/dbpokemon.h" // for FetchPokemon
#include "pokemon/player.h"             // for Genders, UID, Player

class Pokemon;

// clang-format off
const std::string all_pokemon_sql = 
  "SELECT player.player.name, player.player.pkc, player.player.gender, player.team.pokemon_id_0, player.team.pokemon_id_1, player.team.pokemon_id_2, player.team.pokemon_id_3, player.team.pokemon_id_4, player.team.pokemon_id_5 " \
  "FROM player.player INNER JOIN player.team ON (player.player.team_id = player.team.team_id) "\
  "WHERE player_id = \'{}\'";
// clang-format on

Player *FetchPlayer(UID uid) {

    pqxx::nontransaction N(*dbConn->conn);
    pqxx::result R(N.exec(fmt::format(all_pokemon_sql, std::to_string(uid))));

    for (auto c : R) {
        std::string name = c[0].as<std::string>();
        int pkc = c[1].as<int>();
        Genders gender = Genders(c[2].as<int>());
        std::vector<Pokemon *> team;
        int i = 0;
        for (auto p : c.slice(3, 9)) {
            if (!p.is_null()) {
                team.insert(team.begin() + i,
                            FetchPokemon(p.as<std::string>(), N));
            }
            i++;
        }
        N.~nontransaction();
        auto player = new Player(uid, name, gender, team);
        return player;
    }
    N.~nontransaction();
    throw std::runtime_error("Player not found");
}

UID isPlayerRegistered(std::string username) { return 609604248; }