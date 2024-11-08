#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <limits>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

class thoigian
{
private:
    int year, month, day, hour, minute, second;
    string tmtime;
    void isValid() const;
public:
    thoigian(int=0, int=0, int=0, int=0, int=0, int=0);
    void setyear();
    void setmonth();
    void setday();
    void sethour();
    void setminute();
    void setsecond();
    void setinput();
    friend istream &operator>>(istream &, thoigian &);
    friend ostream &operator<<(ostream &, const thoigian &);
    bool operator!=(const thoigian &);
    bool operator==(const thoigian &);
    static bool isLeapYear(int);
};

#endif // TIME_H