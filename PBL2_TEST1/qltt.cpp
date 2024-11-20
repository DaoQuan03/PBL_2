#include "qltt.h"
#include <iostream>

void qltt::creaacc()
{
    cout << "Nhap ten tai khoan: ";
    us.setname();
    cout << "Nhap mat khau: ";
    us.setpassword();
    access.create(us);
}

void qltt::checkacc()
{
    cout << "Nhap ten tai khoan: \n";
    us.setname();
    cout << "Nhap mat khau: \n";
    us.setpassword();
    access.check(us);
    if (access.recheck != 1)
        return checkacc();
    else 
        return;
}

void qltt::credata()
{
    if (access.recheck == 1)
    {
        thoigian tmstt;
        string filename = us.getname() + " " + us.getpass() + ".txt";
        string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
        fs::path filepath = fs::path(foldername) / filename;
        std::ifstream file(filepath);
        string setout;
        if (!file)
        {
            cout << "Khong the truy cap duoc du lieu\n";
            return;
        }
        char check;
        file.get(check);
        if (file.eof())
        {
            cout << "Ban chua tao thong tin cua su kien\n";
        }
        else
        {
            file.unget();
            string line, era, tmtieude, tmmota;
            string tmsave;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, tmsave, '|');
                tmtieude = tmsave;
                getline(ss, tmsave, '|');
                tmmota = tmmota;
                getline(ss, tmsave, ':');
                era = tmsave;
                getline(ss, tmsave, '/');
                tmstt.day = stoi(tmsave);
                getline(ss, tmsave, '/');
                tmstt.month = stoi(tmsave);
                getline(ss, tmsave, '-');
                tmstt.year = stoi(tmsave);
                getline(ss, tmsave, ':');
                tmstt.hour = stoi(tmsave);
                getline(ss, tmsave, ':');
                tmstt.minute = stoi(tmsave);
                getline(ss, tmsave);
                tmstt.second = stoi(tmsave);
                Event tmp(tmtieude, tmmota, tmstt, 0);
                events.push_back(tmp);
                file.close();
            }
        }
    }
}

void qltt::writedata()
{
    vector<string> savevector;
    string tmyear, tmmonth, tmday, tmhour, tmminute, tmsecond, tmsave;
    thoigian tmstt;
    for (int i = 0; i < events.size(); i++)
    {
        tmstt = events[i].getstt();
        tmyear = to_string(tmstt.getyear());
        tmmonth = to_string(tmstt.getmonth());
        tmday = to_string(tmstt.getday());
        tmhour = to_string(tmstt.gethour());
        tmminute = to_string(tmstt.getminute());
        tmsecond = to_string(tmstt.getsecond());
        tmsave = "TIEU DE:" + events[i].gettieude() + "   " + "MO TA:" + events[i].getmota() + "    " + "THOI GIAN BAT DAU:" + tmday + "/" + tmmonth + "/" + tmyear + "-" + tmhour + ":" + tmminute + ":" + tmsecond;
        savevector.push_back(tmsave);
    }
    string filename = us.getname() + " " + us.getpass() + ".txt";
    string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    fs::path filepath = fs::path(foldername) / filename;
    std::ofstream file(filepath);
    if (file.is_open())
    {
        for (int i = 0; i < savevector.size(); i++)
        {
            file << savevector[i] << endl;
        }
        file.close();
    }
    else
    {
        cout << "Khong the truy cap du lieu\n";
    }
}
void qltt::print()
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
        if (ev.getet() != 0)
        {
            cout << "Thoi gian ket thuc: " << ev.getet() << endl;
        }
        cout << "--------------------------------------------" << endl;
    }
}

void qltt::add()
{
    int choice;
    string tmtieude, tmmota;
    thoigian tmstartime, tmendtime;

    cout << "Hay them mot su kien moi" << endl;
    cout << "Nhap tieu de (nhap -1 de quay lai menu): ";
    getline(cin, tmtieude);
    if (tmtieude == "-1") return;

    cout << "Nhap mo ta (nhap -1 de quay lai menu): ";
    getline(cin, tmmota);
    if (tmmota == "-1") return;

    cout << "Nhap thoi gian bat dau (dd/mm/yyyy-hh:mm:ss, nhap -1 de quay lai menu): ";
    if (!tmstartime.setinput())
        return;

    cout << "Ban co muon them thoi gian ket thuc khong?\n";
    cout << "1. Co            2. Khong (nhap -1 de quay lai menu)\n";
    cin >> choice;
    if (choice == -1) return;

    if (choice == 1)
    {
        if (!tmendtime.setinput())
            return;
    }

    Event tmp(tmtieude, tmmota, tmstartime, tmendtime);
    events.push_back(tmp);
}


void qltt::erase()
{
    if (events.empty())
    {
        cout << "Khong co su kien de xoa.\n";
        return;
    }

    cout << "Chon su kien de xoa (nhap -1 de quay lai menu):\n";
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
    if (choice == -1) return;

    if (choice < 1 || choice > events.size())
    {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    events.erase(events.begin() + (choice - 1));
    cout << "Da xoa su kien.\n";
}


void qltt::fix()
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
    cout << "Nhap so thu tu cua su kien can chinh sua (nhap -1 de quay lai menu): ";
    cin >> choice;
    cin.ignore();
    if (choice == -1) return;

    if (choice < 1 || choice > events.size())
    {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    Event &selectedEvent = events[choice - 1];
    string tieude, mota;
    thoigian startTime;

    cout << "Nhap tieu de moi (tieu de hien tai: " << selectedEvent.gettieude() << ", nhap -1 de quay lai): ";
    getline(cin, tieude);
    if (tieude == "-1") return;
    if (!tieude.empty())
    {
        selectedEvent.settieude(tieude);
    }

    cout << "Nhap mo ta moi (mo ta hien tai: " << selectedEvent.getmota() << ", nhap -1 de quay lai): ";
    getline(cin, mota);
    if (mota == "-1") return;
    if (!mota.empty())
    {
        selectedEvent.setmota(mota);
    }

    cout << "Nhap thoi gian bat dau moi (thoi gian hien tai: " << selectedEvent.getstt() << ", nhap -1 de quay lai): ";
    if (!startTime.setinput())
        return;

    selectedEvent.setstt(startTime);
    cout << "Da cap nhat thong tin su kien thanh cong.\n";
}


void qltt::countdown()
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
