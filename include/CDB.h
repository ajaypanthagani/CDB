#ifndef CDB_H
#define CDB_H

class CDB {
public:
    ~CDB();

    bool initialize();
    void run();

private:
    void cleanup();
};

#endif