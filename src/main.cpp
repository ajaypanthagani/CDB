#include <iostream>
#include "cdb.h"

int main() {
    CDB cdb;

    if(cdb.initialize()){
        cdb.run();
    } else {
        std::cerr << "Failed to initialize CDB." << std::endl;
        return -1;
    }

    std::cout << "Application Finished." << std::endl;
    return 0;
}
