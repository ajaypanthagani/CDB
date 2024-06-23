#include <vector>
#include "Database.h"
#include "Table.h"

namespace Model {
    Model::Database::Database(uint64_t id, std::string name){
        this->id = id;
        this->name = name;
    }

    uint64_t Model::Database::getID(){
        return this->id;
    }

    std::string Model::Database::getName(){
        return this->name;
    }

    std::vector<Model::Table> Model::Database::getTables(){
        return this->tables;
    }

    void Model::Database::setName(std::string name){
        this->name = name;
    }

    void Model::Database::setTables(std::vector<Model::Table> tables){
        this->tables = tables;
    }

    void Model::Database::addTable(Model::Table table){
        this->tables.push_back(table);
    }
}