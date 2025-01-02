#include "time.h"

thoigian::thoigian(int y, int m, int d, int h, int mi, int s) : year(y), month(m), day(d), hour(h), minute(mi), second(s) {};

istream &operator>>(istream &is, thoigian &t)
{
    is >> t.hour >> t.minute >> t.second >> t.day >> t.month >> t.year;
    return is;
}

ostream &operator<<(ostream &os, const thoigian &t)
{
    return os << "Luc " << t.hour << "h" << t.minute << "p" << t.second << "s" << " vao ngay " << t.day << "/" << t.month << "/" << t.year;
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
    cout << "Nhap ngay: ";
    cin >> tmday;
    cout << "Nhap thang: ";
    cin >> tmmonth;
    cout << "Nhap nam: ";
    cin >> tmyear;
    cout << "Nhap gio: ";
    cin >> tmhour;
    cout << "Nhap phut: ";
    cin >> tmminute;
    cout << "Nhap giay: ";
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
        cout << "Ngay khong hop le cho thang " << month << ", vui long nhap lai ngay: ";
        cin >> this->day;
        cin.ignore();
    }
    if (this->month < 1 || this->month > 12)
    {
        cout << "Ban da nhap sai quy dinh cua thang(1-12), vui long nhap lai thang: ";
        cin >> this->month;
        cin.ignore();
    }

    if (this->hour < 0 || this->hour > 23)
    {
        cout << "Ban da nhap sai quy dinh cua gio(0-23), vui long nhap lai gio: ";
        cin >> this->hour;
        cin.ignore();
    }
    if (this->minute < 0 || this->minute > 60)
    {
        cout << "Ban da nhap sai quy dinh cua phut(0-60), vui long nhap lai phut: ";
        cin >> this->minute;
        cin.ignore();
    }
    if (this->second < 0 || this->second > 60)
    {
        cout << "Ban da nhap sai quy dinh cua giay(0-60), vui long nhap lai giay: ";
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
    auto now = chrono::system_clock::now();                 // Lấy thời gian của hệ thống
    time_t now_time = chrono::system_clock::to_time_t(now); // Chuyển đổi thời gian hiện tại thành time_t

    // Chuyển đổi thành struct tm
    std::tm *ltm = std::localtime(&now_time); // struct tm lưu trữ các thành phần của thời gian

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
    cout << "Thoi gian ban nhap som hon thoi gian hien tai, vui long nhap lai\n";
    setinput();
    return checktime();
}