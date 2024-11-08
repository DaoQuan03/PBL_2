#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class base_qltt
{
    public:
    virtual void print() = 0;
    virtual void add() = 0;
    virtual void erase() = 0;
    virtual void fix() = 0;
};