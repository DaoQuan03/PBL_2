#include <iostream>
#include "event.h"
#include <string>
#include "qltg.h"

using namespace std;

void qltg::print()
{
    if (events.empty())
    {
        cout << "Khong co su kien de hien thi.\n";
        return;
    }

    for (auto &ev : events)
    {
        cout << "Tieu de: " << ev.gettieude() << endl;
        cout << "Mo ta: " << ev.gettieude() << endl;
        cout << "Thoi gian bat dau: " << ev.getstt() << endl;
        if(ev.getet()!=0)
        {
            cout<<"Thoi gian ket thuc: "<<ev.getet()<<endl;
        }
        cout << "-----------------------------" << endl;
    }
}

void qltg::add()
{
    int choice;
    string tmtieude, tmmota;
    thoigian tmstartime, tmendtime;
    cout << "Hay them mot su kien moi" << endl;
    cout << "Nhap tieu de: ";
    getline(cin, tmtieude);
    cout << "Nhap mo ta: ";
    cin.ignore();
    getline(cin, tmmota);
    cout << "Nhap thoi gian bat dau (dd/mm/yyyy-hh/mm/ss): ";
    tmstartime.setinput();
    cout<<"Ban co muon them thoi gian ket thuc khong\n";
    cout<<"1. Co            2. Khong\n";
    cin>>choice;
    switch (choice)
    {
    case 1:
        tmendtime.setinput();
        break;
    case 2:
        break;
    }
    Event tmp(tmtieude, tmmota, tmstartime, tmendtime);
    events.push_back(tmp);
}

void qltg::erase()
{
    if (events.empty())
    {
        cout << "Khong co su kien de xoa.\n";
        return;
    }

    string tieude;
    thoigian startTime;

    cout << "Nhap tieu de cua su kien can xoa: ";
    cin.ignore();
    getline(cin, tieude);
    cout << "Nhap thoi gian bat dau cua su kien can xoa: ";
    cin >> startTime;
    cin.ignore();

    auto it = find_if(events.begin(), events.end(),
                      [&tieude, &startTime](Event &ev)
                      {
                          return ev.gettieude() == tieude && ev.getstt() == startTime;
                      });

    if (it != events.end())
    {
        events.erase(it);
        cout << "Da xoa su kien.\n";
    }
    else
    {
        cout << "Khong tim thay su kien voi tieu de va thoi gian bat dau nhu da nhap.\n";
    }
}

void qltg::fix()
{
    if (events.empty())
    {
        cout << "Khong co su kien de chinh sua.\n";
        return;
    }
    string tieude, tmtieude,mota;
    thoigian stt, tmstt;
    bool found = false;
    cout<<"Nhap tieu de cua su kien can chinh sua: ";
    getline(cin,tieude);
    cout<<"Nhap thoi gian bat dau cua su kien can chinh sua: ";
    stt.setinput();
    for(int i=0;i<events.size();i++)
    {
        tmtieude=events[i].gettieude();
        tmstt=events[i].getstt();
        if(tieude==tmtieude && stt==tmstt)
        {
            found = true;
            cout<<"Nhap lai tieu de: ";
            getline(cin,tieude);
            cin.ignore();
            cout<<"Nhap lai mo ta: ";
            getline(cin,mota);
            cout<<"Nhap lai thoi gian bat dau: ";
            stt.setinput();
            events[i].settieude(tieude);
            events[i].setmota(mota);
            events[i].setstt(stt);
        }
    }
}

