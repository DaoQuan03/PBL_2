#ifndef EVENT_H
#define EVENT_H

#include "time.h"
#include <string>

class Event
{
private:
    string tieude;
    string mota;
    thoigian startTime;
    thoigian endTime;
    bool operator==(const Event &);

public:
    const string gettieude();
    const string getmota();
    thoigian getstt();
    thoigian getet();
    void settieude(const string);
    void setmota(const string);
    void setstt(const thoigian);
    void setet(const thoigian);
    Event(string = "", string = "", thoigian = 0, thoigian = 0);
};

#endif