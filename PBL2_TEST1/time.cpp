#include "time.h"

thoigian::thoigian(int y, int m, int d, int h, int mi, int s) : year(y), month(m), day(d), hour(h), minute(mi), second(s) {};

void thoigian::isValid() const
{
    bool isValid = true;
    if (this->hour < 0 || this->hour > 23)
    {
        cerr << "Gio khong hop le (0-23). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (this->minute < 0 || this->minute > 59)
    {
        cerr << "Phut khong hop le (0-59). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (this->second < 0 || this->second > 59)
    {
        cerr << "Giay khong hop le (0-59). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (this->month < 1 || this->month > 12)
    {
        cerr << "Thang khong hop le (1-12). Xin hay nhap lai!\n";
        isValid = false;
    }
    int daysInMonth[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (this->day < 1 || this->day > daysInMonth[month])
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