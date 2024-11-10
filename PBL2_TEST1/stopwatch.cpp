#include "stopwatch.h"

stopwatch::stopwatch(int d, int m, int y, int h, int mn, int s) : thoigian()
{
}

stopwatch::~stopwatch()
{
}

int stopwatch::gethour()
{
    return this->hour;
}

int stopwatch::getminute()
{
    return this->minute;
}

int stopwatch::getsecond()
{
    return this->second;
}