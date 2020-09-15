#include "pokemon/database/dbpokemon.h"

#include <fmt/core.h> // for format
#include <pqxx/pqxx>
#include <stdexcept> // for runtime_error
#include <string>    // for string, allocator, basic_string
#include <vector>    // for vector

#include "pokemon/global.h"  // for ElementType, NIL
#include "pokemon/moves.h"   // for Move
#include "pokemon/pokemon.h" // for Stats, Pokemon

// clang-format off
const std::string pokemon_sql = 
  "SELECT player.user_pokemon.nickname, " \
  "public.element_types.element_0, public.element_types.element_1, " \
  "public.base_stats.hp, public.base_stats.attack, public.base_stats.defence, public.base_stats.speed, public.base_stats.sp_attack, public.base_stats.sp_defence, " \
  "player.ev_stats.hp, player.ev_stats.attack, player.ev_stats.defence, player.ev_stats.speed, player.ev_stats.sp_attack, player.ev_stats.sp_defence, " \
  "player.iv_stats.hp, player.iv_stats.attack, player.iv_stats.defence, player.iv_stats.speed, player.iv_stats.sp_attack, player.iv_stats.sp_defence, " \
  "player.user_pokemon.level " \
  "FROM player.user_pokemon " \
  "INNER JOIN player.ev_stats ON (player.user_pokemon.ev_id = player.ev_stats.ev_id) " \
  "INNER JOIN player.iv_stats ON (player.user_pokemon.iv_id = player.iv_stats.iv_id) " \
  "INNER JOIN public.pokemon ON (player.user_pokemon.pokedex_no = public.pokemon.pokedex_no) " \
  "INNER JOIN public.base_stats ON (public.pokemon.base_stats_id = public.base_stats.base_stats_id) " \
  "INNER JOIN public.element_types ON (public.pokemon.element_type_id = public.element_types.element_type_id) WHERE player.user_pokemon.pokemon_id = \'{}\';";

const std::string move_sql = "SELECT player.move.name, player.move.element_type, player.move.damage, player.move.accuracy, player.move.max_pp, player.player_move_bridge.position "\
  "FROM player.player_move_bridge " \
  "INNER JOIN player.move ON (player.player_move_bridge.move_id = player.move.move_id) WHERE player.player_move_bridge.pokemon_id = \'{}\';";

// clang-format on

Stats parseStats(pqxx::row row) {
    if (row.size() == 6) {
        return Stats(row[0].as<int>(), row[1].as<int>(), row[2].as<int>(),
                     row[3].as<int>(), row[4].as<int>(), row[5].as<int>());
    }
    return Stats();
}

std::vector<ElementType> parseElements(pqxx::row row) {
    std::vector<ElementType> ret;
    if (row.size() == 2) {
        ret.push_back(ElementType(row[0].as<int>()));
        ret.push_back(ElementType(row[1].as<int>()));
    }
    ret.push_back(NIL);
    return ret;
}

std::vector<Move *> getMoves(std::string pokemonID, pqxx::nontransaction &N) {
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

Pokemon *FetchPokemon(std::string pokemonID, pqxx::nontransaction &N) {
    pqxx::result R(N.exec(fmt::format(pokemon_sql, pokemonID)));

    for (auto c : R) {
        std::string name = c[0].as<std::string>();
        std::vector<ElementType> types = parseElements(c.slice(1, 3));
        Stats baseStats = parseStats(c.slice(3, 9));
        Stats EV = parseStats(c.slice(9, 15));
        Stats IV = parseStats(c.slice(15, 21));
        int level = c[21].as<int>();
        auto moveset = getMoves(pokemonID, N);
        return new Pokemon(name, types, level, moveset, baseStats, IV, EV);
    }
    N.~nontransaction();
    throw std::runtime_error("Couldn't find pokemon");
}