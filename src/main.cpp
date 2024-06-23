#include <iostream>
#include <map>

#include "domain/dbms.h"

int main() {
    Domain::DBMS::createDatabase("mydatabase");
    Domain::DBMS::createTable("mydatabase", "users", std::vector<std::string>{"id", "username", "password"});
    std::map<std::string, std::string> rowData;
    rowData["id"] = "1";
    rowData["username"] = "some-username";
    rowData["password"] = "some-password";
    Domain::DBMS::insertRow("mydatabase", "users", rowData);
    Domain::DBMS::printTable("mydatabase", "users");
    return 0;
}
