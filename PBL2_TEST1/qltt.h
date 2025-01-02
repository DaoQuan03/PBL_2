#ifndef QLTT_H
#define QLTT_H

#include "event.h"
#include "BASEQLTT.h"
#include "qltc.h"
#include "heapsort.h"

using namespace std;

class qltt : public base_qltt
{
private:
    vector<Event*> events;
    qluser access;

public:
    qltt();
    ~qltt();
    
    void print() override;
    void add() override;
    void erase() override;
    void fix() override;
    bool creacc() override;
    bool checkdata() override;
    void input() override;
    void writedata() override;
    void countdown() override;
    void printcalenda();
    void credata();
    bool isValidNumber(const string &);
    int safeStoi(const string &);
};

#endif // QLTT_H