#include "domain/dbms.h"

namespace Domain {

    void DBMS::createDatabase(const std::string& dbName) {
        fs::path dbPath(Constants::rootDirectory + dbName);
        if (!fs::exists(dbPath)) {
            fs::create_directory(dbPath);
            std::cout << "Database created: " << dbName << std::endl;
        } else {
            std::cout << "Database already exists: " << dbName << std::endl;
        }
    }

    void DBMS::createTable(const std::string& dbName, const std::string& tableName, const std::vector<std::string>& schema) {
        fs::path tablePath(Constants::rootDirectory + dbName + "/" + tableName + Constants::tableFileExtension);
        if (!fs::exists(tablePath)) {
            dbms::Table table;
            table.set_name(tableName);
            for (const auto& field : schema) {
                table.add_schema(field);
            }
            saveTableToFile(tablePath.string(), table);
            std::cout << "Table created: " << tableName << " in database " << dbName << std::endl;
        } else {
            std::cout << "Table already exists: " << tableName << std::endl;
        }
    }

    void DBMS::insertRow(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& rowData) {
        fs::path tablePath(Constants::rootDirectory + dbName + "/" + tableName + Constants::tableFileExtension);
        if (fs::exists(tablePath)) {
            dbms::Table table = loadTableFromFile(tablePath.string());
            dbms::TableRow* newRow = table.add_rows();
            for (const auto& [key, value] : rowData) {
                (*newRow->mutable_fields())[key] = value;
            }
            saveTableToFile(tablePath.string(), table);
            std::cout << "Row inserted into table: " << tableName << std::endl;
        } else {
            std::cerr << "Table does not exist: " << tableName << std::endl;
        }
    }

    void DBMS::printTable(const std::string& dbName, const std::string& tableName) {
        fs::path tablePath(Constants::rootDirectory + dbName + "/" + tableName + Constants::tableFileExtension);
        if (fs::exists(tablePath)) {
            dbms::Table table = loadTableFromFile(tablePath.string());
            std::cout << "Table: " << table.name() << std::endl;
            std::cout << "Schema: ";
            for (const auto& field : table.schema()) {
                std::cout << field << " ";
            }
            std::cout << std::endl;

            for (const auto& row : table.rows()) {
                std::cout << "Row: ";
                for (const auto& [key, value] : row.fields()) {
                    std::cout << key << "=" << value << " ";
                }
                std::cout << std::endl;
            }
        } else {
            std::cerr << "Table does not exist: " << tableName << std::endl;
        }
    }

    void DBMS::saveTableToFile(const std::string& filename, const dbms::Table& table) {
        std::ofstream output(filename, std::ios::binary);
        if (!output) {
            throw std::runtime_error("Failed to open file for writing: " + filename);
        }
        if (!table.SerializeToOstream(&output)) {
            throw std::runtime_error("Failed to serialize table to file: " + filename);
        }
    }

    dbms::Table DBMS::loadTableFromFile(const std::string& filename) {
        std::ifstream input(filename, std::ios::binary);
        if (!input) {
            throw std::runtime_error("Failed to open file for reading: " + filename);
        }
        dbms::Table table;
        if (!table.ParseFromIstream(&input)) {
            throw std::runtime_error("Failed to parse table from file: " + filename);
        }
        return table;
    }

} // namespace Database
