#ifndef QLTT_H
#define QLTT_H

#include "event.h"
#include "BASEQLTT.h"
#include"qltc.h"
#include"heapsort.h"


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
    bool isValidNumber(const std::string& );
    int safeStoi(const std::string& );
};

#endif // QLTT_H