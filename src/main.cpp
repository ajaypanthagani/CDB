#include <iostream>
#include <map>

#include "domain/dbms.h"

int main() {
    // domain::DBMS::createDatabase("newdabase");
    auto databases = domain::DBMS::getDatabases();
    for(auto database: databases){
        std::cout<<database.name()<<std::endl;
    }
    domain::DBMS::createTable("newdabase", "newtableo", {{"id", "int"}, {"username", "string"}, {"password", "string"}});
    domain::DBMS::insertRow("newdabase", "newtableo", {{"id", "1"}, {"username", "apanthagani"}, {"password", "somep@ssword"}});
    auto table = domain::DBMS::getTable("newdabase", "newtableo");

    util::Table::printTable(table);
    return 0;
}
