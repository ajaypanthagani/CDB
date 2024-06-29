#ifndef DATA_UTIL_H
#define DATA_UTIL_H

#include <iostream>
#include <stdexcept>
#include "src/proto/dbms.pb.h"
#include "constants.h"

namespace util {
    class Data {
    public:
        /**
         * \brief converts raw string data to db compatible data.
         * \param table The table that we are inserting data into.
         * \param colName The column that we are inserting data into.
         * \param data The data we want to insert.
         */
        static dbms::Data formatRawDataToDBData(const dbms::Table &table, const std::string &colName, const std::string &data);
    };
} // namespace util

#endif // DATA_UTIL_H