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
        Database();
        ~Database();

        void setName(std::string);
        string getName();
        void addTable(Model::Table);
        void getTables();
    };
}

#endif