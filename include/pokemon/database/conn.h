#ifndef CONN_H
#define CONN_H

#include <string> // for allocator, operator+, char_traits, string

#include "pokemon/global.h" // for getEnvVar

namespace pqxx {
class connection;
} // namespace pqxx

const std::string connString =
    "user=" + getEnvVar("username") + " password=" + getEnvVar("password") +
    " host=" + getEnvVar("hostname") + " port=" + getEnvVar("hostport") +
    " dbname=" + getEnvVar("databasename");

class PGConn {
  public:
    pqxx::connection *conn;
    PGConn();
};

inline PGConn *dbConn;

#endif
