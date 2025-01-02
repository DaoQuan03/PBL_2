#include "heapsort.h"

void heapsort::swap(Event &a, Event &b)
{
    Event tmp = a;
    a = b;
    b = tmp;
}

void heapsort::heapify(vector<Event> &eve, int n, int i)
{
    int smallest = i;
    int right = 2 * i + 2, left = 2 * i + 1;
    if (left < n && eve[left].calltime() < eve[smallest].calltime())
        smallest = left;
    if (right < n && eve[right].calltime() < eve[smallest].calltime())
        smallest = right;
    if (smallest != i)
    {
        swap(eve[i], eve[smallest]);
        heapify(eve, n, smallest);
    }
}

void heapsort::heapsorT(vector<Event> &ev)
{
    int n = ev.size();
    for (int i = n / 2 - 1; i >= 0; i--)        //vi tri n/2-1 duoc goi la nut cha cuoi cung cua cay
        heapify(ev, n, i);
    for (int i = n - 1; i >= 0; i--)
    {
        swap(ev[0], ev[i]);
        heapify(ev, i, 0);
    }
}
