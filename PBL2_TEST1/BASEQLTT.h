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
    virtual bool creacc() = 0;
    virtual void input() =0;
    virtual bool checkdata() = 0;
    virtual void writedata() = 0;
    virtual void countdown() = 0;
};

#endif