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
