#ifndef TABLE_UTIL_H
#define TABLE_UTIL_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <boost/filesystem.hpp>
#include "constants.h"
#include "src/proto/dbms.pb.h"

namespace util {
    class Table {
    public:
        /**
         * \brief Gets path instance of table
         * \param dbName The database name.
         * \param tableName The table name.
         */
        static boost::filesystem::path getTablePath(const std::string& dbName, const std::string& tableName, const bool& tableMustExist);

        /**
         * \brief Prints the contents (schema and rows) of the specified table.
         * \param table The table that needs to be printed.
         */
        static void printTable(const dbms::Table& table);

        /**
         * \brief Saves the given table object to a file.
         * \param filename The name of the file to save the table to.
         * \param table The Table object to serialize and save.
         */
        static void saveTableToFile(const std::string& filename, const dbms::Table& table);

        /**
         * \brief Loads and returns a Table object from the specified file.
         * \param filename The name of the file to load the table from.
         * \return The loaded Table object.
         * \throw std::runtime_error If there's an error loading the table.
         */
        static dbms::Table loadTableFromFile(const std::string& filename);
    };
} // namespace util

#endif // TABLE_UTIL_H