#ifndef QLTC_H
#define QLTC_H

#include "User.h"

class qluser
{
private:
    user use;
public:
    string filename;
    int managercheck;
    int recheck;
    qluser();
    ~qluser();
    void check();
    void create();
    void inputuser();
    void checkmanager();
};

#endif // QLTC_H