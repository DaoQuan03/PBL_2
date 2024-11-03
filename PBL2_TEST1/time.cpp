#include "time.h"

thoigian::thoigian() : year(0), month(0), day(0), hour(0), minute(0), second(0) {};

thoigian::thoigian(int y = 0, int m = 0, int d = 0, int h = 0, int mi = 0, int s = 0) : year(y), month(m), day(d), hour(h), minute(mi), second(s) {};

void thoigian::isValid() const {
    bool isValid = true;
    if (hour < 0 || hour > 23) {
        cerr << "Gio khong hop le (0-23). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (minute < 0 || minute > 59) {
        cerr << "Phut khong hop le (0-59). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (second < 0 || second > 59) {
        cerr << "Giay khong hop le (0-59). Xin hay nhap lai!\n";
        isValid = false;
    }
    if (month < 1 || month > 12) {
        cerr << "Thang khong hop le (1-12). Xin hay nhap lai!\n";
        isValid = false;
    }
    int daysInMonth[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1 || day > daysInMonth[month]) {
        cerr << "Ngay khong hop le cho thang " << month << ". Xin hay nhap lai!\n";
        isValid = false;
    }

    if (!isValid) {
        throw invalid_argument("Ban da nhap sai thong tin thoi gian. Xin hay nhap lai!");
    }
}

istream &operator>>(istream &is, thoigian &t)
{
    while (true) {
        is >> t.hour >> t.minute >> t.second >> t.day >> t.month >> t.year;

        try {
            t.isValid(); 
            break; 
        } catch (const invalid_argument& e) {
            cerr << e.what() << "\n";
            is.clear(); 
            is.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    return is;
}


ostream &operator<<(ostream &os, const thoigian &t)
{
    return os << "Luc " << t.hour << "h" << t.minute << "p" << t.second << "s" << " vao ngay " << t.day << "/"  << t.month << "/" << t.year;
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

bool thoigian::isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
};