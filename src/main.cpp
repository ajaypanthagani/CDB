#include <iostream>
#include <map>

#include "domain/dbms.h"

int main() {
    Domain::DBMS::createDatabase("mydatabase");
    Domain::DBMS::createTable("mydatabase", "users", {{"id", "int"}, {"username", "string"}, {"password", "string"}});
    Domain::DBMS::insertRow("mydatabase", "users", {{"id", "1"}, {"username", "apanthagani"}, {"password", "somep@ssword"}});
    auto table = Domain::DBMS::getTable("mydatabase", "users");
    Domain::DBMS::printTable(table);
    return 0;
}
