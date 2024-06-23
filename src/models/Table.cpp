#include <vector>
#include "Table.h"

namespace Model {
    Model::Table::Table(uint64_t id, std::string name){
        this->id = id;
        this->name = name;
    }

    uint64_t Model::Table::getID(){
        return this->id;
    }

    std::string Model::Table::getName(){
        return this->name;
    }

    void Model::Table::setName(std::string name){
        this->name = name;
    }

    std::vector<Row> Model::Table::getRows(){
        return this->rows;
    }

    void Model::Table::setRows(std::vector<Row> rows){
        this->rows = rows;
    }

    void Model::Table::addRow(Row row){
        this->rows.push_back(row);
    }

}