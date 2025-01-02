#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <vector>
#include <algorithm>
//#include <limits>:cung cap cac hang so  de xac dinh gioi han cua cac kieu du lieu
#include <string>
#include <iomanip>
#include <sstream>      //Thu vien cung cap cac lop de lam viec voi cac chuoi ky tu, cho phep su chuoi ky tu lam nguon du lieu hoac la noi luu tru du lieu
#include <chrono>       //Thu vien dung de lam viec voi thoi gian, tinh toan khoang thoi gian voi cac ham co san va nhung don vi thoi gian khac nhau

using namespace std;

class thoigian
{
public:
    int year, month, day, hour, minute, second;

    thoigian(int=0, int=0, int=0, int=0, int=0, int=0);
    bool setinput();

    friend istream &operator>>(istream &, thoigian &);
    friend ostream &operator<<(ostream &, const thoigian &);
    bool operator!=(const thoigian &);
    bool operator==(const thoigian &);

    static bool isLeapYear(int);
    static thoigian getCurrentTime();
    thoigian timeUntil(const thoigian &other) const;
    void checktime();
    
    void setday(int);
    void setmonth(int);
    void setyear(int);
    void sethour(int);
    void setminute(int);
    void setsecond(int);

    int getyear();
    int getmonth();
    int getday();
    int gethour();
    int getminute();
    int getsecond();
};

#endif // TIME_H