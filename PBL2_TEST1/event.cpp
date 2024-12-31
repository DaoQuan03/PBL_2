#include "event.h"
#include <iostream>
#include <string>
using namespace std;

Event::Event(string tmtieude, string tmmota, thoigian tmstt, thoigian tmet) : tieude(tmtieude), mota(tmmota), startTime(tmstt), endTime(tmet)
{
}
bool Event::operator==(const Event &ev)
{
    return (this->startTime == ev.startTime);
}

const string Event::gettieude()
{
    return this->tieude;
}

const string Event::getmota()
{
    return this->mota;
}

thoigian Event::getstt()
{
    return this->startTime;
}

thoigian Event::getet()
{
    return this->endTime;
}

void Event::settieude(const string tmtieude)
{
    this->tieude = tmtieude;
}

void Event::setmota(const string tmmota)
{
    this->mota = tmmota;
}

void Event::setstt(const thoigian tmstt)
{
    this->startTime = tmstt;
}

void Event::setet(const thoigian tmet)
{
    this->endTime = tmet;
}

double Event::calltime()
{
    tm cal={};
    cal.tm_mday=startTime.getday();
    cal.tm_mon=startTime.getmonth()-1;
    cal.tm_year=startTime.getyear()-1970;
    cal.tm_hour=startTime.gethour();
    cal.tm_min=startTime.getminute();
    cal.tm_sec=startTime.getsecond();

    // Lấy thời gian hiện tại
    auto now = chrono::system_clock::now();
    time_t nowTime = chrono::system_clock::to_time_t(now);

    // Chuyển đổi thời gian nhập và thời gian hiện tại thành std::time_t
    time_t callTimeT = mktime(&cal);       //La mot ham trong thu vien c_time dung de chuyen doi 1 struct_tm sang kieu time_t(la so giay ke tu 1/1/1970)

    // Tính khoảng thời gian chênh lệch
    double difference = difftime(callTimeT, nowTime);      //difftime():dung de tinh toan so giay giua hai thoi diem
    return difference;
}
