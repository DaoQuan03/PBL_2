#ifndef MANAGER_H
#define MANAGER_H

#include"qltc.h"
#include"qltt.h"

class manager:public base_qltt
{
private:
    qltt mana;
    qluser acc;
    vector <user> save;
public:
    manager();
    ~manager();
    void add() override;
    void fix() override;
    void print() override;
    void erase() override;
};

#endif // MANAGER_H