#ifndef QLTG_H
#define QLTG_H

#include "time.h"
#include "event.h"
#include "BASEQLTT.h"

using namespace std;

class qltg : public base_qltt
{
private:
    vector<Event> events;
public:
    void print() override;
    void add() override;
    void erase() override;
    void fix() override;
    void countdown() override;
};

#endif //QLTG_H