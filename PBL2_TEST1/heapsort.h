#ifndef HEAPSORT_H
#define HEAPSORT_H

#include"qltt.h"

class heapsort
{
public:
    void swap(Event *, Event *);
    void heapify(vector<Event*>, int , int );
    void heapsorT(vector<Event*>);
};

#endif // HEAPSORT_H
