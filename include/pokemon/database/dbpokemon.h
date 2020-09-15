#ifndef DBPOKEMON_H
#define DBPOKEMON_H

#include <string>

namespace pqxx {
class nontransaction;
}

class Pokemon;

Pokemon *FetchPokemon(std::string playerID, pqxx::nontransaction &N);

#endif
