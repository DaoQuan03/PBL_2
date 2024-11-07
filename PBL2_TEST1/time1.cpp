#include "time.h"

thoigian::thoigian(int y , int m, int d , int h , int mi , int s ) : year(y), month(m), day(d), hour(h), minute(mi), second(s) {};

void thoigian::isValid() const
{
    bool isValid = true;
    if (hour < 0 || hour > 23)
    {
        cerr << "Gio khong hop le (0-23). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (minute < 0 || minute > 59)
    {
        cerr << "Phut khong hop le (0-59). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (second < 0 || second > 59)
    {
        cerr << "Giay khong hop le (0-59). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (month < 1 || month > 12)
    {
        cerr << "Thang khong hop le (1-12). Xin hay nhap lai!\n";
        isValid = false;
    }
    int daysInMonth[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1 || day > daysInMonth[month])
    {
        cerr << "Ngay khong hop le cho thang " << month << ". Xin hay nhap lai!\n";
        isValid = false;
    }

    if (!isValid)
    {
        throw invalid_argument("Ban da nhap sai thong tin thoi gian. Xin hay nhap lai!");
    }
}

istream &operator>>(istream &is, thoigian &t)
{
    while (true)
    {
        is >> t.hour >> t.minute >> t.second >> t.day >> t.month >> t.year;

        try
        {
            t.isValid();
            break;
        }
        catch (const invalid_argument &e)
        {
            cerr << e.what() << "\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
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

bool thoigian::isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
};

void thoigian::setyear()
{
    cin >> this->year;
    string tmyear;
    tmyear = to_string(this->year);
    this->tmtime.push_back(tmyear);
    cin>>tmyear;
    this->tmtime.push_back(tmyear);
    
}

void thoigian::setmonth()
{
    cin >> this->month;
    string tmmonth;
    tmmonth = to_string(this->month);
    this->tmtime.push_back(tmmonth);
    cin>>tmmonth;
    this->tmtime.push_back(tmmonth);
}

void thoigian::setday()
{
    cin >> this->day;
    string tmday;
    tmday = to_string(this->day);
    this->tmtime.push_back(tmday);
    cin>>tmday;
    this->tmtime.push_back(tmday);
}

void thoigian::sethour()
{
    cin >> this->hour;
    string tmhour;
    tmhour = to_string(this->hour);
    this->tmtime.push_back(tmhour);
    cin>>tmhour;
    this->tmtime.push_back(tmhour);
}

void thoigian::setminute()
{
    cin >> this->minute;
    string tmminute;
    tmminute = to_string(this->minute);
    this->tmtime.push_back(tmminute);
    cin>>tmminute;
    this->tmtime.push_back(tmminute);
}

void thoigian::setsecond()
{
    cin >> this->second;
    string tmsecond;
    tmsecond = to_string(this->second);
    this->tmtime.push_back(tmsecond);
}

void thoigian::cre_set()
{
    thoigian tmp;
    tmp.setday();
    tmp.setmonth();
    tmp.setyear();
    tmp.sethour();
    tmp.setminute();
    tmp.setsecond();
}