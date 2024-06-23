#ifndef CDB_H
#define CDB_H
#include <iostream>

class CDB {
public:
    ~CDB();

    bool initialize();
    void run();

private:
    void cleanup();
};

#endif