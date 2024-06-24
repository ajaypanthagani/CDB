#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <stdexcept> // For std::runtime_error
#include <iomanip>
#include <boost/filesystem.hpp>
#include "src/proto/dbms.pb.h"
#include "constants.h"
#include "util/data.h"

namespace fs = boost::filesystem;

namespace Domain {

    /**
     * \brief Manages databases and tables, providing functionalities like creating databases,
     * tables, inserting rows
     */
    class DBMS {
    public:
        /**
         * \brief Creates a new database with the given name.
         * \param dbName The name of the database to create.
         */
        static void createDatabase(const std::string& dbName);

        /**
         * \brief Creates a new table with the given name and schema in the specified database.
         * \param dbName The name of the database.
         * \param tableName The name of the table to create.
         * \param schema The schema (fields) of the table.
         */
        static void createTable(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& schema);

        /**
         * \brief gets the table with the given name in the specified database.
         * \param dbName The name of the database.
         * \param tableName The name of the table to get.
         */
        static dbms::Table getTable(const std::string& dbName, const std::string& tableName);

        /**
         * \brief Inserts a new row into the specified table of the database.
         * \param dbName The name of the database.
         * \param tableName The name of the table to insert into.
         * \param rowData The data (fields and values) of the new row to insert.
         */
        static void insertRow(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& rowData);

        /**
         * \brief Prints the contents (schema and rows) of the specified table.
         * \param table The table that needs to be printed.
         */
        static void printTable(const dbms::Table& table);

    private:
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

} // namespace Database

#endif // DATABASE_MANAGER_H
