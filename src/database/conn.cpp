#include "pokemon/database/conn.h"

#include <iostream>            // for operator<<, endl, basic_ostream, cout
#include <pqxx/connection.hxx> // for connection

PGConn::PGConn() {
    auto C = new pqxx::connection(connString);
    if (C->is_open()) {
        std::cout << "Opened database successfully: " << C->dbname() << std::endl;
    } else {
        std::cout << "Can't open database" << std::endl;
    }
    this->conn = C;
}