#include "util/data.h"

namespace util {
    dbms::Data Data::formatRawDataToDBData(const dbms::Table &table, const std::string &colName, const std::string &data) {
        auto schema = table.schema();
        auto it = schema.find(colName);
        if (it == schema.end()) {
            throw std::runtime_error("Column not found in schema: " + colName);
        }
        auto colType = it->second;

        dbms::Data dbData;
        try {
            if (colType == Constants::DataType::INT) {
                dbData.set_int_value(std::stoi(data));
            } else if (colType == Constants::DataType::DOUBLE) {
                dbData.set_double_value(std::stod(data));
            } else if (colType == Constants::DataType::STRING) {
                dbData.set_string_value(data);
            } else if (colType == Constants::DataType::BOOL) {
                dbData.set_bool_value(data == "true");
            } else {
                throw std::runtime_error("Unknown data type: " + colType);
            }
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("Invalid argument `" + data + "` for `" + colName + "` of type `" + colType + "`");
        } catch (const std::out_of_range& e) {
            throw std::runtime_error("Data size out of range when setting value `" + data + "` for `" + colName + "` of type `" + colType + "`");
        } catch (const std::exception& e) {
            throw std::runtime_error("Exception when setting value `" + data + "` for `" + colName + "` of type `" + colType + "`");
        }

        return dbData;
    }
} // namespace util
