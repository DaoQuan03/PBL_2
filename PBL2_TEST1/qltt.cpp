#include "qltt.h"
#include <iostream>

void qltt::creacc()
{
    rightmanager = 0;
    access.inputuser();
    access.checkmanager();
    if (access.managercheck)
    {
        rightmanager = 1;
        return;
    }
    else
    {
        access.create();
        if (access.recheck != 1)
            return creacc();
        else
            return;
    }
}

void qltt::checkdata()
{
    rightmanager = 0;
    access.inputuser();
    access.checkmanager();
    if (access.managercheck)
    {
        rightmanager = 1;
        return;
    }
    else
    {
        access.check();
        if (access.recheck != 1)
            return checkdata();
        else
            return;
    }
}

bool qltt::isValidNumber(const string &s) //Kiem tra xem chuoi dau vao co phai la 1 so hoac rong hay khong
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit); //neu chuoi rong, tra ve false
                                                                //all_of(begin,end,condition): kiem tra tat ca cac phan tu trong day co thoa man dieu kien nao do hay khong
}                                                               //::isdigit: kiem tra 1 ky tu co phai la 1 so tu 0-9 hay khong

int qltt::safeStoi(const string &s)
{
    if (isValidNumber(s))
    {
        return stoi(s);
    }
    throw invalid_argument("Invalid number: " + s); //la mot ngoai le(exception), dung de thong bao 1 doi so khong hop le da duoc truyen vao
}

void qltt::credata()
{
    if (access.recheck == 1)
    {
        thoigian tmstt, tmet;
        string input = access.filename;
        string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
        fs::path filepath = fs::path(foldername) / input;
        ifstream file(filepath);
        if (!file)
        {
            cout << "Khong the truy cap duoc du lieu\n";
            return;
        }
        char check;
        file.get(check);    //Lay ki tu dau tien de kiem tra xem da co du lieuu ve su kien cua nguoi dung trong data chua
        if (file.eof())     //Kiem tra con tro da di den cuoi cung chua
        {
            cout << "Ban chua tao thong tin cua su kien\n";
        }
        else
        {
            file.unget();    //Neu co du lieu, tra lai ki tu dau tien vua lay o tren
            string line, tmtieude, tmmota;
            string tmsave;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, tmsave, '|');
                tmtieude = tmsave;
                getline(ss, tmsave, '|');
                tmmota = tmsave;
                getline(ss, tmsave, '/');
                tmstt.day = safeStoi(tmsave);
                getline(ss, tmsave, '/');
                tmstt.month = safeStoi(tmsave);
                getline(ss, tmsave, '-');
                tmstt.year = safeStoi(tmsave);
                getline(ss, tmsave, ':');
                tmstt.hour = safeStoi(tmsave);
                getline(ss, tmsave, ':');
                tmstt.minute = safeStoi(tmsave);
                getline(ss, tmsave,'|');
                tmstt.second = safeStoi(tmsave);

                // Kiểm tra nếu không còn ký tự sau khi gán tmstt.second
                if (ss.rdbuf()->in_avail() != 0) // kiểm tra còn dữ liệu trong bộ nhớ đệm của stringstream hay không
                                                 //rdbuf()(read buffer): la mot phuong thuc cua doi tuong stream, dung de tra ve 1 con tro lien ket voi bo nho dem cua 1 doi tuong stream
                                                 //in_avail(): dung de tra ve so byte con lai trong bo nho dem truoc khi duoc truyen vao doi tuong stream, neu bang khong thi khong co du lieu trong nguon
                {
                    getline(ss, tmsave, '/');
                    tmet.day = safeStoi(tmsave);
                    if (tmet.day > 0)
                    {
                        getline(ss, tmsave, '/');
                        tmet.month = safeStoi(tmsave);
                        getline(ss, tmsave, '-');
                        tmet.year = safeStoi(tmsave);
                        getline(ss, tmsave, ':');
                        tmet.hour = safeStoi(tmsave);
                        getline(ss, tmsave, ':');
                        tmet.minute = safeStoi(tmsave);
                        getline(ss, tmsave);
                        tmet.second = safeStoi(tmsave);
                    }
                }

                Event tmp(tmtieude, tmmota, tmstt, tmet);
                events.push_back(tmp);
            }
            file.close();
        }
    }
}

void qltt::writedata()
{
    vector<string> savevector;
    string tmtieude, tmmota, tmyear, tmmonth, tmday, tmhour, tmminute, tmsecond, tmsave;
    thoigian tmstt, tmet;
    for (int i = 0; i < events.size(); i++)
    {
        tmet = events[i].getet();
        tmtieude = events[i].gettieude();
        tmmota = events[i].getmota();
        tmstt = events[i].getstt();
        tmyear = to_string(tmstt.getyear());
        tmmonth = to_string(tmstt.getmonth());
        tmday = to_string(tmstt.getday());
        tmhour = to_string(tmstt.gethour());
        tmminute = to_string(tmstt.getminute());
        tmsecond = to_string(tmstt.getsecond());
        tmsave = tmtieude + "|" + tmmota + "|" + tmday + "/" + tmmonth + "/" + tmyear + "-" + tmhour + ":" + tmminute + ":" + tmsecond;
        if (tmet.getday() > 0)
        {
            tmyear = to_string(tmet.getyear());
            tmmonth = to_string(tmet.getmonth());
            tmday = to_string(tmet.getday());
            tmhour = to_string(tmet.gethour());
            tmminute = to_string(tmet.getminute());
            tmsecond = to_string(tmet.getsecond());
            tmsave = tmsave + "|" + tmday + "/" + tmmonth + "/" + tmyear + "-" + tmhour + ":" + tmminute + ":" + tmsecond;
        }
        savevector.push_back(tmsave);
    }
    string input = access.filename;
    string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    fs::path filepath = fs::path(foldername) / input;
    ofstream file(filepath);
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
    heapsort sort;
    sort.heapsorT(events);
    for (auto &ev : events)
    {
        cout << "Tieu de:" << ev.gettieude() << endl;
        cout << "Mo ta: " << ev.getmota() << endl;
        cout << "Thoi gian bat dau: " << ev.getstt() << endl;
        thoigian tmet = ev.getet();
        if (tmet.day > 0)
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
    if (tmtieude == "-1")
        return;

    cout << "Nhap mo ta (nhap -1 de quay lai menu): ";
    getline(cin, tmmota);
    if (tmmota == "-1")
        return;

    cout << "Nhap thoi gian bat dau\n";
    if (!tmstartime.setinput())
        return;

    cout << "Ban co muon them thoi gian ket thuc khong?\n";
    cout << "1. Co            2. Khong (nhap -1 de quay lai menu)\n";
    cin >> choice;
    if (choice == -1)
        return;

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
    if (choice == -1)
        return;

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
        cout << "- Ket thuc: " << events[i].getet() << endl;
    }

    int choice;
    cout << "Nhap so thu tu cua su kien can chinh sua (nhap -1 de quay lai menu): ";
    cin >> choice;
    cin.ignore();
    if (choice == -1)
        return;

    if (choice < 1 || choice > events.size())
    {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    Event &selectedEvent = events[choice - 1];
    string tieude, mota;
    thoigian startTime, endTime;

    cout << "Nhap tieu de moi (tieu de hien tai: " << selectedEvent.gettieude() << ", nhap -1 de quay lai): ";
    getline(cin, tieude);
    if (tieude == "-1")
        return;
    if (!tieude.empty())
    {
        selectedEvent.settieude(tieude);
    }

    cout << "Nhap mo ta moi (mo ta hien tai: " << selectedEvent.getmota() << ", nhap -1 de quay lai): ";
    getline(cin, mota);
    if (mota == "-1")
        return;
    if (!mota.empty())
    {
        selectedEvent.setmota(mota);
    }

    cout << "Nhap thoi gian bat dau moi (thoi gian hien tai: " << selectedEvent.getstt() << ", nhap -1 de quay lai): ";
    if (!startTime.setinput())
        return;
    int choose;
    cout << "Ban co muon them thoi gian ket thuc khong?\n";
    cout << "1. Co            2. Khong (nhap -1 de quay lai menu)\n";
    cin >> choose;
    if (choose == -1)
        return;

    if (choose == 1)
    {
        if (!endTime.setinput())
            return;
    }
    selectedEvent.setstt(startTime);
    selectedEvent.setet(endTime);
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

