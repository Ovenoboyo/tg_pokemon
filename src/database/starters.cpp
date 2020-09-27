#include <algorithm>                       // for move, sample, copy, max
#include <boost/lexical_cast.hpp>          // for lexical_cast
#include <boost/uuid/random_generator.hpp> // for random_generator, rando...
#include <boost/uuid/uuid_io.hpp>          // for operator<<
#include <fmt/core.h>                      // for format
#include <ios>                             // for ios_base::failure
#include <iterator>                        // for back_insert_iterator
#include <pqxx/pqxx>                       // for nontransaction
#include <pqxx/transaction.hxx>            // for work
#include <random>                          // for random_device, mt19937
#include <stddef.h>                        // for size_t
#include <string>                          // for string, basic_string
#include <vector>                          // for vector

#include "pokemon/database/conn.h" // for starterHolder, PGConn
#include "pokemon/pokemon.h"       // for Stats, generateIV
#include "pokemon/user/player.h"   // for Genders, UID

// clang-format on
const std::string starter_sql =
    "SELECT public.pokemon.name, public.pokemon.pokedex_no FROM "
    "public.starters INNER JOIN public.pokemon ON (public.starters.pokedex_no "
    "= public.pokemon.pokedex_no);";

const std::string insertStats = "INSERT INTO player.{0} ({1}, hp, attack, "
                                "defence, sp_attack, sp_defence, speed) "
                                "VALUES ('{2}', {3});";
const std::string insertPlayerPokemon =
    "INSERT INTO player.user_pokemon (pokemon_id, pokedex_no, ev_id, iv_id, "
    "nickname, level) "
    "VALUES ('{0}', {1}, '{2}', '{3}', '{4}', {5})";

const std::string insertTeamPokemon =
    "INSERT INTO player.team (team_id, pokemon_id_{0}) "
    "VALUES ('{1}', '{2}');";

const std::string insertPlayer =
    "INSERT INTO player.player (player_id, team_id, name, gender, pkc) "
    "VALUES ('{0}', '{1}', '{2}', {3}, {4})";

// clang-format off

std::vector<starterHolder> PGConn::getStarters() {
    pqxx::nontransaction N(*conn);
    pqxx::result R(N.exec(starter_sql));

    std::vector<starterHolder> starters;
    for (auto c : R) {
        starters.push_back(starterHolder{c[0].as<std::string>(), c[1].as<int>()});
    }
    return starters;
}

void PGConn::registerStarter(UID userID, std::string username, int pokedexNo, Genders gender) {
    auto moveset = getMoveSetByLevel(pokedexNo, 5);
    if (moveset.size() > 4) {
        std::vector<int> tmp;
        size_t n = 4;
        std::sample(
            moveset.begin(),
            moveset.end(),
            std::back_inserter(tmp),
            n,
            std::mt19937{std::random_device{}()}
        );
        moveset.clear();
        std::move(tmp.begin(), std::next(tmp.begin()), std::back_inserter(moveset));
    }

    auto IVStats = generateIV();
    Stats EVStats = Stats(0, 0, 0, 0, 0, 0);

    auto IVID = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
    auto EVID = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
    auto PokemonID = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
    auto TeamID = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
    
    pqxx::work W(*conn);
    W.exec(fmt::format(insertStats, "iv_stats", "iv_id", IVID, IVStats.Serialize()));
    W.exec(fmt::format(insertStats, "ev_stats", "ev_id", EVID, EVStats.Serialize()));
    W.exec(fmt::format(insertPlayerPokemon, PokemonID, pokedexNo, EVID, IVID, "kek", 5));
    W.exec(fmt::format(insertTeamPokemon, 0, TeamID, PokemonID));
    W.exec(fmt::format(insertPlayer, userID, TeamID, username, gender, 50));
    W.exec(insertMovesQuery(moveset, PokemonID));
    W.commit();
}