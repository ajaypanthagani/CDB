#include "cdb.h"

CDB::~CDB() {
    cleanup();
}

bool CDB::initialize(){
    std::cout << "Initializing..." << std::endl;
    return true;
}

void CDB::run(){
    std::cout << "Running..." << std::endl;
}

void CDB::cleanup(){
    std::cout << "Cleaning..." << std::endl;
}