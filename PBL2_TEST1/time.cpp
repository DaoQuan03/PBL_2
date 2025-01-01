#include "time.h"

thoigian::thoigian(int y, int m, int d, int h, int mi, int s) : year(y), month(m), day(d), hour(h), minute(mi), second(s) {};

istream &operator>>(istream &is, thoigian &t)
{
    is >> t.hour >> t.minute >> t.second >> t.day >> t.month >> t.year;
    return is;
}

ostream &operator<<(ostream &os, const thoigian &t)
{
    return os << "At " << t.hour << "h" << t.minute << "m" << t.second << "s" << " on " << t.day << "/" << t.month << "/" << t.year;
}

bool thoigian::operator==(const thoigian &dt1)
{
    return (this->second == dt1.second &&
            this->minute == dt1.minute &&
            this->hour == dt1.hour &&
            this->day == dt1.day &&
            this->month == dt1.month &&
            this->year == dt1.year);
};

bool thoigian::operator!=(const thoigian &dt1)
{
    return (this->second != dt1.second &&
            this->minute != dt1.minute &&
            this->hour != dt1.hour &&
            this->day != dt1.day &&
            this->month != dt1.month &&
            this->year != dt1.year);
};

bool thoigian::isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
};

bool thoigian::setinput()
{
    int tmday, tmmonth, tmyear, tmhour, tmminute, tmsecond;
    cout << "Enter day: ";
    cin >> tmday;
    cout << "Enter month: ";
    cin >> tmmonth;
    cout << "Enter year: ";
    cin >> tmyear;
    cout << "Enter hour: ";
    cin >> tmhour;
    cout << "Enter minute: ";
    cin >> tmminute;
    cout << "Enter second: ";
    cin >> tmsecond;

    setday(tmday);
    setmonth(tmmonth);
    setyear(tmyear);
    sethour(tmhour);
    setminute(tmminute);
    setsecond(tmsecond);

    int daysInMonth[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (this->day < 1 || this->day > daysInMonth[month])
    {
        cout << "The day is not valid for the month " << month << ", please enter the day again: ";
        cin >> this->day;
        cin.ignore();
    }
    if (this->month < 1 || this->month > 12)
    {
        cout << "You entered an incorrect month (1-12), please enter the month again: ";
        cin >> this->month;
        cin.ignore();
    }

    if (this->hour < 0 || this->hour > 23)
    {
        cout << "You entered an incorrect hour (0-23), please enter the hour again: ";
        cin >> this->hour;
        cin.ignore();
    }
    if (this->minute < 0 || this->minute > 60)
    {
        cout << "You entered an incorrect minute (0-60), please enter the minute again: ";
        cin >> this->minute;
        cin.ignore();
    }
    if (this->second < 0 || this->second > 60)
    {
        cout << "You entered an incorrect second (0-60), please enter the second again: ";
        cin >> this->second;
        cin.ignore();
    }
    checktime();
    cout << endl;
    return true;
}

thoigian thoigian::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *ltm = std::localtime(&now_time);

    return thoigian(
        ltm->tm_year + 1900,
        ltm->tm_mon + 1,
        ltm->tm_mday,
        ltm->tm_hour,
        ltm->tm_min,
        ltm->tm_sec);
}

thoigian thoigian::timeUntil(const thoigian &other) const
{
    std::tm thisTime = {second, minute, hour, day, month - 1, year - 1900};
    std::tm otherTime = {other.second, other.minute, other.hour, other.day, other.month - 1, other.year - 1900};

    std::time_t this_t = std::mktime(&thisTime);
    std::time_t other_t = std::mktime(&otherTime);

    int secondsRemaining = static_cast<int>(std::difftime(other_t, this_t));

    thoigian countdown;
    countdown.day = secondsRemaining / (24 * 3600);
    secondsRemaining %= (24 * 3600);
    countdown.hour = secondsRemaining / 3600;
    secondsRemaining %= 3600;
    countdown.minute = secondsRemaining / 60;
    countdown.second = secondsRemaining % 60;

    return countdown;
}

void thoigian::setday(int day)
{
    this->day = day;
}

void thoigian::setmonth(int month)
{
    this->month = month;
}

void thoigian::setyear(int year)
{
    this->year = year;
}

void thoigian::sethour(int hour)
{
    this->hour = hour;
}

void thoigian::setminute(int minute)
{
    this->minute = minute;
}

void thoigian::setsecond(int second)
{
    this->second = second;
}

int thoigian::getyear() 
{
    return this->year;
}

int thoigian::getmonth() 
{
    return this->month;
}

int thoigian::getday() 
{
    return this->day;
}

int thoigian::gethour() 
{
    return this->hour;
}

int thoigian::getminute()
{
    return this->minute;
}

int thoigian::getsecond()
{
    return this->second;
}

void thoigian::checktime()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    std::tm *ltm = std::localtime(&now_time);

    int daysys = ltm->tm_mday, monthsys = ltm->tm_mon + 1, yearsys = ltm->tm_year + 1900, hoursys = ltm->tm_hour, minsys = ltm->tm_min, secsys = ltm->tm_sec;

    if (this->year > yearsys)
    {
        return;
    }
    if (this->year == yearsys)
    {
        if (this->month > monthsys)
        {
            return;
        }
        if (this->month == monthsys)
        {
            if (this->day > daysys)
            {
                return;
            }
            if (this->day == daysys)
            {
                if (this->hour > hoursys)
                {
                    return;
                }
                if (this->hour == hoursys)
                {
                    if (this->minute > minsys)
                    {
                        return;
                    }
                    if (this->minute == minsys)
                    {
                        if (this->second > secsys)
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << "The time you entered is earlier than the current time, please enter the time again\n";
    setinput();
    return checktime();
}
