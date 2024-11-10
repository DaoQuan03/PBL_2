#include "qlttstopwatch.h"

void qlttstopwatch::add()
{
    string enter;
    cout << "Nhan enter de bat dau chuong trinh,nhan s de hien thi thoi gian da troi qua, e de ket thuc chuong trinh\n";
    int tmhour = timestopwatch.gethour(), tmminute = timestopwatch.getminute(), tmsecond = timestopwatch.getsecond();
    auto start_time = chrono::steady_clock::now();
    chrono::steady_clock::time_point end_time;
    while (true)
    {
        cin>>enter;
        if (enter.empty())
        {
            start_time = chrono::steady_clock::now();
        }
        else if (enter == "s")
        {
            end_time = chrono::steady_clock::now();
            tmsecond = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();
            if (tmsecond > 60)
            {
                tmminute += tmsecond / 60;
                tmsecond %= 60;
            }
            else if (tmminute > 60)
            {
                tmhour += tmminute / 60;
                tmminute %= 60;
            }
            else if (tmhour > 23)
            {
                tmhour %= 24;
                return;
            }
            cout<<tmhour<<"h"<<tmminute<<"p"<<tmsecond<<"s";
        }
        else
        {
            break;
        }
    }
}

void qlttstopwatch::print()
{
}

void qlttstopwatch::erase()
{
}

void qlttstopwatch::fix()
{
}