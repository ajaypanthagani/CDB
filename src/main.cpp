#include <iostream>
#include "CDB.h"

using namespace std;

int main() {
    CDB cdb;

    if(cdb.initialize()){
        cdb.run();
    } else {
        cerr << "Failed to initialize CDB." << endl;
        return -1;
    }

    std::cout << "Application Finished." << std::endl;
    return 0;
}
