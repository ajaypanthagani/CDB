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

    void DBMS::createTable(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& schema) {
        fs::path tablePath(Constants::rootDirectory + dbName + "/" + tableName + Constants::tableFileExtension);
        if (!fs::exists(tablePath)) {
            dbms::Table table;
            table.set_name(tableName);

            for(const auto& [name, type] : schema){
                (*table.mutable_schema())[name] = type;
            }

            saveTableToFile(tablePath.string(), table);
            std::cout << "Table created: " << tableName << " in database " << dbName << std::endl;
        } else {
            std::cout << "Table already exists: " << tableName << std::endl;
        }
    }

    dbms::Table DBMS::getTable(const std::string& dbName, const std::string& tableName) {
        fs::path tablePath(Constants::rootDirectory + dbName + "/" + tableName + Constants::tableFileExtension);
        if (fs::exists(tablePath)) {
            return loadTableFromFile(tablePath.string());
        } else {
            std::cerr << "Table does not exist: " << tableName << std::endl;
            throw std::runtime_error("Table does not exist: " + tableName);
        }
    }

    void DBMS::insertRow(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& rowData) {
        fs::path tablePath(Constants::rootDirectory + dbName + "/" + tableName + Constants::tableFileExtension);
        if (fs::exists(tablePath)) {
            dbms::Table table = loadTableFromFile(tablePath.string());
            dbms::Row* newRow = table.add_rows();

            for (const auto& [col, val] : rowData) {
                auto data = Util::formatRawDataToDBData(table, col, val);
                data.set_string_value(val);
                (*newRow->mutable_fields())[col] = data;
            }

            saveTableToFile(tablePath.string(), table);
            std::cout << "Row inserted into table: " << tableName << std::endl;
        } else {
            std::cerr << "Table does not exist: " << tableName << std::endl;
        }
    }

    void DBMS::printTable(const dbms::Table& table) {
        // Print table name
        std::cout << "Table: " << table.name() << std::endl;

        // Print schema (column names)
        std::cout << "+";
        for (const auto& [colName, colType] : table.schema()) {
            std::cout << std::setw(15) << std::setfill('-') << "-" << "+";
        }
        std::cout << std::endl;

        std::cout << "|";
        for (const auto& [colName, colType] : table.schema()) {
            std::cout << std::setw(15) << std::setfill(' ') << colName << "|";
        }
        std::cout << std::endl;

        std::cout << "+";
        for (const auto& [colName, colType] : table.schema()) {
            std::cout << std::setw(15) << std::setfill('-') << "-" << "+";
        }
        std::cout << std::endl;

        // Print rows
        for (const auto& row : table.rows()) {
            std::cout << "|";
            for (const auto& [colName, colType] : table.schema()) {
                auto it = row.fields().find(colName);
                if (it != row.fields().end()) {
                    const dbms::Data& data = it->second;
                    std::string value;

                    switch (data.type_case()) {
                        case dbms::Data::kIntValue:
                            value = std::to_string(data.int_value());
                            break;
                        case dbms::Data::kDoubleValue:
                            value = std::to_string(data.double_value());
                            break;
                        case dbms::Data::kStringValue:
                            value = data.string_value();
                            break;
                        case dbms::Data::kBoolValue:
                            value = data.bool_value() ? "true" : "false";
                            break;
                        default:
                            value = "NULL";
                            break;
                    }
                    std::cout << std::setw(15) << std::setfill(' ') << value << "|";
                } else {
                    std::cout << std::setw(15) << std::setfill(' ') << "NULL" << "|";
                }
            }
            std::cout << std::endl;
        }

        std::cout << "+";
        for (const auto& [colName, colType] : table.schema()) {
            std::cout << std::setw(15) << std::setfill('-') << "-" << "+";
        }
        std::cout << std::endl;
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
