#ifndef QLTT_H
#define QLTT_H

#include "event.h"
#include "BASEQLTT.h"
#include"qltc.h"


using namespace std;

class qltt : public base_qltt
{
private:
    vector<Event> events;
    qluser access;
public:
    string setout;
    int rightmanager;
    void print() override;
    void add() override;
    void erase() override;
    void fix() override;
    void countdown();
    void credata();
    void writedata();
    void creacc();
    void checkdata();
};

#endif // QLTT_H