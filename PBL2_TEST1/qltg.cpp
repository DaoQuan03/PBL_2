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
        cout << "Mo ta: " << ev.getmota() << endl;
        cout << "Thoi gian bat dau: " << ev.getstt() << endl;
        if(ev.getet()!=0)
        {
            cout<<"Thoi gian ket thuc: "<<ev.getet()<<endl;
        }
        cout << "--------------------------------------------" << endl;
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
    getline(cin, tmmota);
    cout << "Nhap thoi gian bat dau (dd/mm/yyyy-hh:mm:ss): ";
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

    cout << "Chon su kien de xoa:\n";
    for (int i = 0; i < events.size(); ++i)
    {
        cout << i + 1 << ". " << endl;
        cout << "- Tieu de: " << events[i].gettieude() << endl;
        cout << "- Mo ta: " << events[i].getmota() << endl;
        cout << "- Bat dau: " << events[i].getstt() << endl;
    }
    int choice;
    cout << "Nhap so thu tu cua su kien: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > events.size())
    {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    events.erase(events.begin() + (choice - 1));
    cout << "Da xoa su kien.\n";
}

void qltg::fix()
{
    if (events.empty())
    {
        cout << "Khong co su kien de chinh sua.\n";
        return;
    }

    cout << "Danh sach su kien:\n";
    for (int i = 0; i < events.size(); ++i)
    {
        cout << i + 1 << ". " << endl;
        cout << "- Tieu de: " << events[i].gettieude() << endl;
        cout << "- Mo ta: " << events[i].getmota() << endl;
        cout << "- Bat dau: " << events[i].getstt() << endl;
    }

    int choice;
    cout << "Nhap so thu tu cua su kien can chinh sua: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > events.size())
    {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    Event &selectedEvent = events[choice - 1];
    string tieude, mota;
    thoigian startTime;

    cout << "Nhap tieu de moi (tieu de hien tai: " << selectedEvent.gettieude() << "): ";
    getline(cin, tieude);
    if (!tieude.empty())
    {
        selectedEvent.settieude(tieude);
    }

    cout << "Nhap mo ta moi (mo ta hien tai: " << selectedEvent.getmota() << "): ";
    getline(cin, mota);
    if (!mota.empty())
    {
        selectedEvent.setmota(mota);
    }

    cout << "Nhap thoi gian bat dau moi (thoi gian hien tai: " << selectedEvent.getstt() << "): ";
    startTime.setinput();
    selectedEvent.setstt(startTime);

    cout << "Da cap nhat thong tin su kien thanh cong.\n";
}

void qltg::countdown()
{
    if (events.empty())
    {
        cout << "Khong co su kien de dem nguoc.\n";
        return;
    }

    cout << "Chon su kien de dem nguoc:\n";
    for (int i = 0; i < events.size(); ++i)
    {
        cout << i + 1 << ". " << endl;
        cout << "- Tieu de: " << events[i].gettieude() << endl;
        cout << "- Mo ta: " << events[i].getmota() << endl;
        cout << "- Bat dau: " << events[i].getstt() << endl;
             
    }

    int choice;
    cout << "Nhap so thu tu cua su kien: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > events.size())
    {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    thoigian currentTime = thoigian::getCurrentTime();
    thoigian eventTime = events[choice - 1].getstt();
    thoigian timeRemaining = currentTime.timeUntil(eventTime);

    cout << "Thoi gian con lai den su kien \"" << events[choice - 1].gettieude() << "\":\n";
    cout << timeRemaining.day << " ngay, " << timeRemaining.hour << " gio, " 
         << timeRemaining.minute << " phut, " << timeRemaining.second << " giay.\n";
}