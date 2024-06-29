#include "domain/dbms.h"

namespace domain {

    void DBMS::createDatabase(const std::string& dbName) {
        fs::path dbPath(Constants::rootDirectory + dbName);

        if (fs::exists(dbPath)) {
            throw std::runtime_error("Database already exists: " + dbName);
        }

        fs::create_directory(dbPath);
    }

    std::vector<dbms::Database> DBMS::getDatabases() {
        fs::path cdbRoot(Constants::rootDirectory);

        std::vector<dbms::Database> databases;
        fs::recursive_directory_iterator end;
        for (fs::recursive_directory_iterator i(cdbRoot); i != end; ++i){
            const fs::path  file = (*i);
            if(fs::is_directory(file)){
                dbms::Database database;
                database.set_name(file.filename().string());
                databases.push_back(database);
            }
        }

        return databases;
    }

    void DBMS::createTable(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& schema) {
        auto tablePath = util::Table::getTablePath(dbName, tableName, false);

        dbms::Table table;
        table.set_name(tableName);
        for(const auto& [name, type] : schema){
            (*table.mutable_schema())[name] = type;
        }

        util::Table::saveTableToFile(tablePath.string(), table);
    }

    dbms::Table DBMS::getTable(const std::string& dbName, const std::string& tableName) {
        auto tablePath = util::Table::getTablePath(dbName, tableName, true);
        return util::Table::loadTableFromFile(tablePath.string());
    }

    void DBMS::insertRow(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& rowData) {
        auto tablePath = util::Table::getTablePath(dbName, tableName, true);

        dbms::Table table = util::Table::loadTableFromFile(tablePath.string());
        dbms::Row* newRow = table.add_rows();
        for (const auto& [col, val] : rowData) {
            auto data = util::Data::formatRawDataToDBData(table, col, val);
            data.set_string_value(val);
            (*newRow->mutable_fields())[col] = data;
        }

        util::Table::saveTableToFile(tablePath.string(), table);
    }
} // namespace domain
