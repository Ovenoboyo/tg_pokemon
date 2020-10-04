#include <algorithm>    // for max
#include <pqxx/row.hxx> // for row, row::reference
#include <vector>       // for vector

#include "pokemon/database/conn.h" // for parseElements, parseStats
#include "pokemon/global.h"        // for ElementType, NIL
#include "pokemon/pokemon.h"       // for Stats

Stats parseStats(pqxx::row row) {
    if (row.size() == 6) {
        return Stats(row[0].as<int>(), row[1].as<int>(), row[2].as<int>(), row[3].as<int>(), row[4].as<int>(),
                     row[5].as<int>());
    }
    return Stats();
}

std::vector<ElementType> parseElements(pqxx::row row) {
    std::vector<ElementType> ret;
    if (row.size() == 2) {
        ret.push_back(ElementType(row[0].as<int>()));
        if (!row[1].is_null()) {
            ret.push_back(ElementType(row[1].as<int>()));
        }
    }
    ret.push_back(NIL);
    return ret;
}