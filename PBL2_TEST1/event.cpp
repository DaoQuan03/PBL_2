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
    std::tm target_tm = {};
    target_tm.tm_year = startTime.getyear() - 1900; // tm_year tính từ năm 1900
    target_tm.tm_mon = startTime.getmonth() - 1;    // tm_mon từ 0 đến 11
    target_tm.tm_mday = startTime.getday();
    target_tm.tm_hour = startTime.gethour();
    target_tm.tm_min = startTime.getsecond();
    target_tm.tm_sec = startTime.getsecond();

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_time);

    // Chuyển đổi thời gian mục tiêu thành time_t
    std::time_t target_time = std::mktime(&target_tm);

    // Tính khoảng thời gian
    auto target = std::chrono::system_clock::from_time_t(target_time);
    auto duration = target - now;

    // Chuyển đổi khoảng thời gian thành giây
    auto seconds = std::chrono::duration<double>(duration).count();
    return seconds;
}
