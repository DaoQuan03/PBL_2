#ifndef QLTG_H
#define QLTG_H

#include <iostream>
#include <vector>
#include "event.h"
#include "BASEQLTT.h"
using namespace std;

class qltg:public base_qltt
{
private:
    vector<Event> events;
public:
    void print() override;
    void add() override;
    void erase() override;
    void fix() override;
};

#endif  