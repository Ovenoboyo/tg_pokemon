#include <fmt/core.h> // for format
#include <pqxx/pqxx>  // for nontransaction
#include <stdexcept>  // for runtime_error
#include <string>     // for string, allocator, basic_string
#include <vector>     // for vector

#include "pokemon/database/conn.h" // for PGConn
#include "pokemon/global.h"        // for ElementType
#include "pokemon/moves.h"         // for Move

// clang-format on
const std::string moveset_by_level_sql =
    "SELECT move_id FROM public.pokemon_move_bridge WHERE "
    "(public.pokemon_move_bridge.pokedex_no = {0} AND "
    "public.pokemon_move_bridge.level <= {1}) ORDER BY "
    "public.pokemon_move_bridge.level ASC;";

const std::string move_sql =
    "SELECT public.move.name, public.move.element_type, public.move.damage, "
    "public.move.accuracy, public.move.max_pp, "
    "player.player_move_bridge.position "
    "FROM player.player_move_bridge "
    "INNER JOIN public.move ON (player.player_move_bridge.move_id = "
    "public.move.move_id) WHERE player.player_move_bridge.pokemon_id = \'{}\';";

const std::string insertMoves = "INSERT INTO player.player_move_bridge "
                                "(move_id, pokemon_id, position) VALUES ";
// clang-format off

std::vector<int> PGConn::getMoveSetByLevel(int pokedexNo, int level) {
    pqxx::nontransaction N(*conn);
    std::vector<int> moveset;
    pqxx::result R(N.exec(fmt::format(moveset_by_level_sql, pokedexNo, level)));
    N.~nontransaction();
    for (auto c : R) {
        moveset.push_back(c.at(0).as<int>());
    }
    return moveset;
}

std::vector<Move *> PGConn::getMoves(std::string pokemonID, pqxx::nontransaction &N) {
    pqxx::result R(N.exec(fmt::format(move_sql, pokemonID)));

    std::vector<Move *> moveset;

    for (auto c : R) {
        auto move =
            new Move(c[0].as<std::string>(), ElementType(c[1].as<int>()),
                     c[2].as<int>(), c[3].as<int>(), c[4].as<int>());
        moveset.insert(moveset.begin() + c[5].as<int>(), move);
    }
    if (moveset.size() < 1) {
        N.~nontransaction();
        throw std::runtime_error("No moves for pokemon");
    }
    return moveset;
}

std::string PGConn::insertMovesQuery(std::vector<int> moves, std::string pokemonID) {
    std::string ret = insertMoves;
    int i = 0;
    for (auto moveID : moves) {
        ret += fmt::format("({}, '{}', {})", moveID, pokemonID, i);
        if (i != moves.size() - 1) {
            ret += ", ";
        }
        i++;
    }
    return ret;
}