#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class thoigian
{
private:
    int year, month, day, hour, minute, second;
    void isValid() const;
public:
    thoigian();
    thoigian(int, int, int, int, int, int);

    friend istream &operator>>(istream &, thoigian &);
    friend ostream &operator<<(ostream &, const thoigian &);

    bool operator==(const thoigian &);
    static bool isLeapYear(int);
};

#endif // TIME_H