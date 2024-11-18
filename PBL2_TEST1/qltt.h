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
    user us;
public:
    string setout;
    void print() override;
    void add() override;
    void erase() override;
    void fix() override;
    void countdown();
    void credata();
    void writedata();
    void creaacc();
    void checkacc();
};

#endif // QLTT_H