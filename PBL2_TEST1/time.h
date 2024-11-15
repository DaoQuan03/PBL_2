#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
using namespace std;

class thoigian
{
public:
    int year, month, day, hour, minute, second;
    string tmtime;
public:
    thoigian(int=0, int=0, int=0, int=0, int=0, int=0);
    void setinput();
    friend istream &operator>>(istream &, thoigian &);
    friend ostream &operator<<(ostream &, const thoigian &);
    bool operator!=(const thoigian &);
    bool operator==(const thoigian &);
    static bool isLeapYear(int);

    static thoigian getCurrentTime();
    thoigian timeUntil(const thoigian &other) const;
};

#endif // TIME_H