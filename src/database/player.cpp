#include <fmt/core.h>              // for format
#include <memory>                  // for shared_ptr, allocator, make_shared
#include <pqxx/field.hxx>          // for field
#include <pqxx/nontransaction.hxx> // for nontransaction
#include <pqxx/pqxx>               // IWYU pragma: keep
#include <pqxx/result.hxx>         // for result
#include <pqxx/row.hxx>            // for row, row::reference
#include <stdint.h>                // for int32_t
#include <string>                  // for string, basic_string, to_string
#include <utility>                 // for move
#include <vector>                  // for vector

#include "pokemon/database/conn.h" // for PGConn, NotRegisteredException
#include "pokemon/user/player.h"   // for Player, UID, Genders, INVALID_ID

class Pokemon;

// clang-format off
const std::string all_pokemon_sql = 
  "SELECT player.player.name, player.player.pkc, player.player.gender, player.team.pokemon_id_0, player.team.pokemon_id_1, player.team.pokemon_id_2, player.team.pokemon_id_3, player.team.pokemon_id_4, player.team.pokemon_id_5 " \
  "FROM player.player INNER JOIN player.team ON (player.player.team_id = player.team.team_id) "\
  "WHERE player_id = '{}'";

const std::string registered_sql = "SELECT player_id FROM player.player WHERE player.player.name = '{}'";

const std::string registered_sql_uid = "SELECT EXISTS(SELECT 1 FROM player.player WHERE player.player.player_id='{}') LIMIT 1 ";
// clang-format on

Player::Ptr PGConn::FetchPlayer(UID uid) {
    pqxx::nontransaction N(*conn);
    pqxx::result R(N.exec(fmt::format(all_pokemon_sql, std::to_string(uid))));

    for (auto c : R) {
        std::string name = c[0].as<std::string>();
        // int pkc = c[1].as<int>();
        Genders gender = Genders(c[2].as<int>());
        std::vector<Pokemon::Ptr> team;
        int i = 0;
        for (auto p : c.slice(3, 9)) {
            if (!p.is_null()) {
                team.insert(team.begin() + i, FetchUserokemon(p.as<std::string>(), N));
            }
            i++;
        }
        N.~nontransaction();
        auto player = std::make_shared<Player>(uid, name, gender, std::move(team));
        return player;
    }
    N.~nontransaction();
    throw NotRegisteredException(std::to_string(uid));
}

UID PGConn::isPlayerRegistered(std::string username) {
    pqxx::nontransaction N(*conn);
    pqxx::result R(N.exec(fmt::format(registered_sql, username)));
    N.~nontransaction();
    return (R.size() > 0) ? ((R.at(0).at(0).is_null()) ? INVALID_ID : R.at(0).at(0).as<int32_t>()) : INVALID_ID;
}

bool PGConn::isPlayerRegistered(UID uid) {
    pqxx::nontransaction N(*conn);
    pqxx::result R(N.exec(fmt::format(registered_sql_uid, uid)));
    N.~nontransaction();
    return (R.size() > 0) ? ((R.at(0).at(0).is_null()) ? false : (R.at(0).at(0).as<std::string>().compare("t") == 0))
                          : false;
}