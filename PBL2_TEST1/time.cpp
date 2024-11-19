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

void thoigian::setinput()
{
    getline(cin, tmtime);
    int cnt = 0;
    for (char x : tmtime)
    {
        if (x == '/' || x == '-' || x == ':')
        {
            cnt++;
        }
    }
    if (cnt > 5)
    {
        cout << "Ban da nhap sai dinh dang, vui long nhap lai(dd/mm/yyyy-hh:mm:ss): ";
        getline(cin, tmtime);
    }
    string tmsave;
    stringstream ss(tmtime);

    getline(ss, tmsave, '/');
    this->day = stoi(tmsave);
    getline(ss, tmsave, '/');
    this->month = stoi(tmsave);
    getline(ss, tmsave, '-');
    this->year = stoi(tmsave);
    getline(ss, tmsave, ':');
    this->hour = stoi(tmsave);
    getline(ss, tmsave, ':');
    this->minute = stoi(tmsave);
    getline(ss, tmsave);
    this->second = stoi(tmsave);

    int daysInMonth[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (this->day < 1 || this->day > daysInMonth[month])
    {
        cout << "Ngay khong hop le cho thang " << month << ", vui long nhap lai ngay: ";
        cin >> this->day;
    }
    if (this->month < 1 || this->month > 12)
    {
        cout << "Ban da nhap sai quy dinh cua thang(1-12), vui long nhap lai thang: ";
        cin >> this->month;
    }
    if (this->year < 2024)
    {
        cout << "Ban da nhap sai quy dinh cua nam(>2024), vui long nhap lai nam: ";
        cin >> this->year;
    }
    if (this->hour < 0 || this->hour > 23)
    {
        cout << "Ban da nhap sai quy dinh cua gio(0-23), vui long nhap lai gio: ";
        cin >> this->hour;
    }
    if (this->minute < 0 || this->minute > 60)
    {
        cout << "Ban da nhap sai quy dinh cua phut(0-60), vui long nhap lai phut: ";
        cin >> this->minute;
    }
    if (this->second < 0 || this->second > 60)
    {
        cout << "Ban da nhap sai quy dinh cua giay(0-60), vui long nhap lai giay: ";
        cin >> this->second;
    }
    cout << endl;
}

thoigian thoigian::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *ltm = std::localtime(&now_time);

    return thoigian(
        ltm->tm_year + 1900,
        ltm->tm_mon + 1,
        ltm->tm_mday,
        ltm->tm_hour,
        ltm->tm_min,
        ltm->tm_sec
    );
}

thoigian thoigian::timeUntil(const thoigian &other) const {
    std::tm thisTime = { second, minute, hour, day, month - 1, year - 1900 };
    std::tm otherTime = { other.second, other.minute, other.hour, other.day, other.month - 1, other.year - 1900 };

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