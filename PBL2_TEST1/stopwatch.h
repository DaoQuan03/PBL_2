#include "time.h"

class stopwatch : public thoigian
{
public:
    stopwatch(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
    int gethour();
    int getminute();
    int getsecond();
    ~stopwatch();
};
