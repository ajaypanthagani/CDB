#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <vector>
#include "Constants.h"

namespace Model {
    typedef std::vector<std::pair<std::string, std::string>> Schema;
    typedef std::vector<Constants::ColumnDataTypeVariant> Row;

    class Table {
    private:
        uint64_t id;
        std::string name;
        std::vector<Row> rows;
        Schema schema;
    public:
        Table(uint64_t, std::string);

        uint64_t getID();
        std::string getName();
        std::vector<Row> getRows();
        void setName(std::string);
        void setRows(std::vector<Row>)
        void addRow(Row row);
    };
}

#endif