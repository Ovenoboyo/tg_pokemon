#include <fmt/core.h>               // for format
#include <pqxx/nontransaction.hxx>  // for nontransaction
#include <pqxx/result.hxx>          // for result
#include <pqxx/row.hxx>             // for row, row::reference
#include <memory>                   // for make_shared, allocator, shared_ptr
#include <pqxx/pqxx>                // IWYU pragma: keep
#include <stdexcept>                // for runtime_error
#include <string>                   // for string, basic_string
#include <vector>                   // for vector

#include "pokemon/database/conn.h"  // for parseStats, PGConn, parseElements
#include "pokemon/global.h"         // for ElementType, NORMAL, FLYING
#include "pokemon/moves.h"          // for Move
#include "pokemon/pokemon.h"        // for Pokemon, Stats

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

// clang-format on

std::shared_ptr<Pokemon> PGConn::FetchUserokemon(std::string pokemonID,
                                 pqxx::nontransaction &N) {
    pqxx::result R(N.exec(fmt::format(pokemon_sql, pokemonID)));

    for (auto c : R) {
        std::string name = c[0].as<std::string>();
        std::vector<ElementType> types = parseElements(c.slice(1, 3));
        Stats baseStats = parseStats(c.slice(3, 9));
        Stats EV = parseStats(c.slice(9, 15));
        Stats IV = parseStats(c.slice(15, 21));
        int level = c[21].as<int>();
        auto moveset = getMoves(pokemonID, N);
        return std::make_shared<Pokemon>(name, types, level, moveset, baseStats, IV, EV);
    }
    N.~nontransaction();
    throw std::runtime_error("Couldn't find pokemon");
}

std::shared_ptr<Pokemon> PGConn::GetWildPokemon(int route_no) {
    std::vector<ElementType> types = {NORMAL, FLYING};
    std::vector<Move *> moveset = {new Move("Tackle", NORMAL, 69, 100, 32)};
    Stats stats = Stats{1, 1, 1, 1, 1, 1};
    return std::make_shared<Pokemon>("Nigga Cheese", types, 69, moveset, stats, stats, stats);
}