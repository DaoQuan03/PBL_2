#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class CountdownTimer {
private:
    int seconds; 

public:
    CountdownTimer(int);
    void start();
};

#endif //COUNTDOWN_H