#include "heapsort.h"

void heapsort::swap(Event *a, Event *b)
{
    Event *tmp = a;
    a = b;
    b = tmp;
}

void heapsort::heapify(vector<Event*> eve, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && eve[left]->calltime() > eve[largest]->calltime())
        largest = left;

    if (right < n && eve[right]->calltime() > eve[largest]->calltime())
        largest = right;

    if (largest != i)
    {
        swap(eve[i], eve[largest]);
        heapify(eve, n, largest);
    }
}

void heapsort::heapsorT(vector<Event*> ev)
{
    int n = ev.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(ev, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(ev[0], ev[i]);
        heapify(ev, i, 0);
    }
}
