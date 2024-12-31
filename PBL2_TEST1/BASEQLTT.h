#ifndef BASEQLTT_H
#define BASEQLTT_H


using namespace std;

class base_qltt
{
    public:
    virtual void print() = 0;
    virtual void add() = 0;
    virtual void erase() = 0;
    virtual void fix() = 0;
};

#endif