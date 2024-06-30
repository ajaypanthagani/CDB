#include <iostream>
#include <map>

#include "domain/dbms.h"

int main() {
    domain::DBMS::createDatabase("newdatabase");
    auto databases = domain::DBMS::getDatabases();
    for(auto database: databases){
        std::cout<<database.name()<<std::endl;
    }
    domain::DBMS::createTable("newdatabase", "newtableo", {{"id", "int"}, {"username", "string"}, {"password", "string"}});
    domain::DBMS::insertRow("newdatabase", "newtableo", {{"id", "1"}, {"username", "apanthagani"}, {"password", "somep@ssword"}});
    domain::DBMS::insertRow("newdatabase", "newtableo", {{"id", "2"}, {"username", "apanthagani"}, {"password", "somep@ssword"}});
    domain::DBMS::insertRow("newdatabase", "newtableo", {{"id", "3"}, {"username", "apanthagani"}, {"password", "somep@ssword"}});
    domain::DBMS::insertRow("newdatabase", "newtableo", {{"id", "4"}, {"username", "apanthagani"}, {"password", "somep@ssword"}});
    int rowsDeleted = domain::DBMS::deleteRow("newdatabase", "newtableo", {{"id", "1"}});
    auto table = domain::DBMS::getTable("newdatabase", "newtableo");

    util::Table::printTable(table);
    return 0;
}
