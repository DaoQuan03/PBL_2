#ifndef MANAGER_H
#define MANAGER_H

#include "qltc.h"
#include "qltt.h"

class manager : public base_qltt 
{
private:
    qluser acc; 
    vector<user> save;  
public:
    manager();      
    ~manager();       
    void add() override;      
    void fix() override;      
    void print() override;      
    void erase() override;     
    bool creacc() override;    
    bool checkdata() override;
    void input() override; 
    void writedata() override;  
    void countdown() override;  
};

#endif // MANAGER_H
