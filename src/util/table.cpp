#include "util/table.h"

namespace util {
    boost::filesystem::path Table::getTablePath(const std::string& dbName, const std::string& tableName, const bool& tableMustExist) {
        boost::filesystem::path tablePath(Constants::rootDirectory + dbName + "/" + tableName + Constants::tableFileExtension);

        if (tableMustExist && !boost::filesystem::exists(tablePath)) {
            throw std::runtime_error("Table does not exist: " + tableName);
        }

        return tablePath;
    }

    void Table::saveTableToFile(const std::string& filename, const dbms::Table& table) {
        std::ofstream output(filename, std::ios::binary);
        if (!output) {
            throw std::runtime_error("Failed to open file for writing: " + filename);
        }

        if (!table.SerializeToOstream(&output)) {
            throw std::runtime_error("Failed to serialize table to file: " + filename);
        }
    }

    dbms::Table Table::loadTableFromFile(const std::string& filename) {
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

    void Table::printTable(const dbms::Table& table) {
        std::cout << "Table: " << table.name() << std::endl;

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
} // namespace util
