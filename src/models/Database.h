#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include <vector>
#include "Table.h"

namespace Model {
    class Database {
    private:
        uint64_t id;
        std::string name;
        std::vector<Model::Table> tables;
    public:
        Database(uint64_t, std::string);

        uint64_t getID();
        std::string getName();
        std::vector<Model::Table> getTables();
        void setName(std::string);
        void setTables(std::vector<Model::Table>);
        void addTable(Model::Table);
    };
}

#endif