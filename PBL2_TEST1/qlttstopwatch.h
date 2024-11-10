#include "stopwatch.h"
#include "BASEQLTT.h"

class qlttstopwatch : public base_qltt
{
    stopwatch timestopwatch;

public:
    void add() override;
    void print() override;
    void erase() override;
    void fix() override;
};