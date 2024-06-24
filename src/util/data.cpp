#include "util/data.h"

namespace Util {
    dbms::Data formatRawDataToDBData(const dbms::Table &table, const std::string &colName, const std::string &data) {
        auto schema = table.schema();
        auto colType = schema[colName];

        dbms::Data dbData;
        try{
            if (colType == Constants::DataType::INT) {
                dbData.set_int_value(std::stoi(data));
            } else if (colType == Constants::DataType::DOUBLE) {
                dbData.set_double_value(std::stod(data));
            } else if (colType == Constants::DataType::STRING) {
                dbData.set_string_value(data);
            } else if (colType == Constants::DataType::BOOL) {
                dbData.set_bool_value(data == "true");
            } else {
                throw std::runtime_error("unknown data type " + colType);
            }
        } catch(const std::exception& e){
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("exception when setting value " + data + " for " + colName + "of type " + colType);
        }

        return dbData;
    }
}