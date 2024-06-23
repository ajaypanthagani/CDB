#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <variant>
#include <string>

namespace Constants {
    using ColumnDataTypeVariant = std::variant<std::string, int, bool>;
}

#endif
