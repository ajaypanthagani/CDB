#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept> // For std::runtime_error
#include <iomanip>
#include <boost/filesystem.hpp>
#include "src/proto/dbms.pb.h"
#include "constants.h"
#include "util/data.h"
#include "util/table.h"

namespace fs = boost::filesystem;

namespace domain {

    /**
     * \brief Manages databases and tables, providing functionalities like creating databases,
     * tables, inserting rows
     */
    class DBMS {
    public:
        /**
         * \brief Give list of all databases
         */
        static std::vector<dbms::Database> getDatabases();

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
         * \brief Deletes a matching rows from the specified table of the database.
         * \param dbName The name of the database.
         * \param tableName The name of the table to delete from.
         * \param rowData The data (fields and values) of the rows to delete.
         */
        static int deleteRow(const std::string& dbName, const std::string& tableName, const std::map<std::string, std::string>& rowData);
    };

} // namespace domain

#endif // DATABASE_MANAGER_H
