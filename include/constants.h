#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>

namespace Constants {
    extern const std::string rootDirectory;
    extern const std::string tableFileExtension;

    struct DataType {
        static const std::string INT;
        static const std::string DOUBLE;
        static const std::string STRING;
        static const std::string BOOL;
    };
}

#endif
