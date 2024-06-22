#include <iostream>
#include "CDB.h"

using namespace std;

CDB::~CDB() {
    cleanup();
}

bool CDB::initialize(){
    cout << "Initializing..." << endl;
    return true;
}

void CDB::run(){
    cout << "Running..." << endl;
}

void CDB::cleanup(){
    cout << "Cleaning..." << endl;
}