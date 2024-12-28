#include "manager.h"

manager::manager()
{
}

manager::~manager()
{
}

void manager::print()
{
    string basedata = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    try
    {
        if (fs::exists(basedata) && fs::is_directory(basedata))
        {
            int i = 0;
            user use;
            string tmp, tmname, tmpass;
            for (const auto &it : fs::directory_iterator(basedata))
            {
                cout << i + 1 << "." << it.path().filename().string() << endl;
                tmp = it.path().filename().string();
                stringstream ss(tmp);
                getline(ss, tmname, '-');
                use.setname(tmname);
                getline(ss, tmpass, '.');
                use.setpassword(tmpass);
                save.push_back(use);
                i++;
            }
        }
        else
        {
            cout << "Loi! Loi khi truy cap duoc du lieu\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Khong the truy cap duoc du lieu" << e.what() << '\n';
    }
}

void manager::add()
{
    user ustmp;
    string tmpname, tmppass;
    cin.ignore();
    cout << "Nhap ten chu nhan muon: ";
    getline(cin, tmpname);
    cout << "Nhap mat khau chu nhan muon: ";
    getline(cin, tmppass);
    ustmp.setname(tmpname);
    ustmp.setpassword(tmppass);
    save.push_back(ustmp);
    string base = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    string accname = ustmp.getname() + "-" + ustmp.getpass() + ".txt";
    if (!fs::exists(base))
    {
        cout << "DATABASE da bi loi" << endl;
        fs::create_directory(base);
    }
    else if (!fs::is_directory(base))
    {
        cout << "Loi khi them 1 pham nhan" << endl;
        return;
    }

    fs::path accpath = fs::path(base) / accname;
    ofstream newacc(accpath);
    if (newacc.is_open())
    {
        cout << "Chu nhan da them tai khoan thanh cong" << endl;
        newacc.close();
        int choice;
        vector<Event> events;
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

        cout << "Nhap thoi gian bat dau (dd/mm/yyyy-hh:mm:ss, nhap -1 de quay lai menu): ";
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

        vector<string> savevector;
        string tmptieude, tmpmota, tmyear, tmmonth, tmday, tmhour, tmminute, tmsecond, tmsave;
        thoigian tmstt, tmet;
        for (int i = 0; i < events.size(); i++)
        {
            tmet = events[i].getet();
            tmptieude = events[i].gettieude();
            tmpmota = events[i].getmota();
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
        string inputmp = ustmp.getname() + "-" + ustmp.getpass() + "txt";
        string input = inputmp;
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
        return;
    }
    else
    {
        cout << "Xin loi chu nhan, tieu nhan vo dung khong the thuc hien duoc" << endl;
        return;
    }
}

void manager::fix()
{
    print();
    cout << "Nhap so thu tu nguoi dung chu nhan muon thay doi\n";
    int choose;
    cin >> choose;
    cin.ignore();
    bool done = false;
    for (int i = 0; i < save.size(); i++)
    {
        if (i == choose - 1)
        {
            int choosen = -1;
            do
            {
                cout << "Chu nhan muon toi thuc hien dieu gi~~\n";
                cout << "1. Thay doi ten va mat khau nguoi dung\n";
                cout << "2. Thay doi du lieu nguoi dung\n";
                cout << "0. Thoat\n";
                cin >> choosen;
                cin.ignore();

                string tmname, tmpass, tmpold, base, tmpnew;
                fs::path oldacc, newacc;
                switch (choosen)
                {
                case 1:
                    cout << "Nhap ten chu nhan muon: ";
                    getline(cin, tmname);
                    cout << "Nhap mat khau chu nhan muon: ";
                    getline(cin, tmpass);
                    tmpold = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    cout << tmpold << endl;
                    save[i].setname(tmname);
                    save[i].setpassword(tmpass);
                    base = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
                    oldacc = fs::path(base) / tmpold;
                    tmpnew = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    newacc = fs::path(base) / tmpnew;

                    if (fs::exists(oldacc))
                    {
                        try
                        {
                            fs::rename(oldacc, newacc);
                            cout << "Chuc mung chu nhan da thanh cong\n";
                        }
                        catch (const std::exception &e)
                        {
                            cerr << "OPP! A em da bi loi: " << e.what() << '\n';
                        }
                    }
                    else
                    {
                        cout << "Base khong ton tai.\n";
                    }
                    break;
                case 2:
                {
                    vector<Event> events;
                    thoigian tmstt, tmet;
                    string tpname = save[i].getname(), tppass = save[i].getpass();
                    string input = tpname + "-" + tppass + ".txt";
                    cout << input << endl;
                    string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
                    fs::path filepath = fs::path(foldername) / input;
                    ifstream file(filepath);
                    if (!file)
                    {
                        cout << "Khong the truy cap duoc du lieu\n";
                        return;
                    }
                    char check;
                    file.get(check);
                    if (file.eof())
                    {
                        cout << "Tai khoan nay chua co thong tin su kien\n";
                        return;
                    }
                    else
                    {
                        file.unget();
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
                            tmstt.day = stoi(tmsave);
                            getline(ss, tmsave, '/');
                            tmstt.month = stoi(tmsave);
                            getline(ss, tmsave, '-');
                            tmstt.year = stoi(tmsave);
                            getline(ss, tmsave, ':');
                            tmstt.hour = stoi(tmsave);
                            getline(ss, tmsave, ':');
                            tmstt.minute = stoi(tmsave);
                            getline(ss, tmsave, '|');
                            tmstt.second = stoi(tmsave);
                            // Kiểm tra nếu không còn ký tự sau khi gán tmstt.second
                            if (ss.rdbuf()->in_avail() != 0) // kiểm tra còn dữ liệu trong bộ nhớ đệm của stringstream hay không
                                                             // rdbuf()(read buffer): la mot phuong thuc cua doi tuong stream, dung de tra ve 1 con tro lien ket voi bo nho dem cua 1 doi tuong stream
                                                             // in_avail(): dung de tra ve so byte con lai trong bo nho dem truoc khi duoc truyen vao doi tuong stream, neu bang khong thi khong co du lieu trong nguon
                            {
                                getline(ss, tmsave, '/');
                                tmet.day = stoi(tmsave);
                                cout << tmet.day << endl;

                                if (tmet.day > 0)
                                {
                                    getline(ss, tmsave, '/');
                                    tmet.month = stoi(tmsave);
                                    getline(ss, tmsave, '-');
                                    tmet.year = stoi(tmsave);
                                    getline(ss, tmsave, ':');
                                    tmet.hour = stoi(tmsave);
                                    getline(ss, tmsave, ':');
                                    tmet.minute = stoi(tmsave);
                                    getline(ss, tmsave);
                                    tmet.second = stoi(tmsave);
                                }
                            }

                            Event tmp(tmtieude, tmmota, tmstt, tmet);
                            events.push_back(tmp);
                        }
                        file.close();
                    }
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
                    cout << startTime;
                    vector<string> savevector;
                    string tmtieude, tmmota, tmyear, tmmonth, tmday, tmhour, tmminute, tmsecond, tmsave;
                    thoigian tmpstt = selectedEvent.getstt();
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
                    string inacc = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    string basename = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
                    fs::path basepath = fs::path(basename) / inacc;
                    ofstream accpath(basepath);
                    if (accpath.is_open())
                    {
                        for (int i = 0; i < savevector.size(); i++)
                        {
                            accpath << savevector[i] << endl;
                        }
                        file.close();
                    }
                    else
                    {
                        cout << "Khong the truy cap du lieu\n";
                    }
                }
                break;
                case 0:
                    cout << "Thoat chuong trinh.\n";
                    done = true;
                    break;
                default:
                    cout << "Lua chon khong hop le, vui long chon lai.\n";
                }
            } while (choosen != 0);
        }
        if (done)
            break;
    }
}

void manager::erase()
{
    cout << "Danh sach nguoi dung: " << endl;
    print();
    cout << "Nhap so thu tu tai khoan chu nhan muon xoa\n";
    int choice;
    cin >> choice;
    if (choice > save.size() - 1)
    {
        cout << "Lua chon cua chu nhan da vuot qua so ke pham trong tran tuc, xin chu nhan nhap lai\n";
        return erase();
    }
    else
    {
        for (int i = 0; i < save.size() - 1; i++)
        {
            if (i == choice - 1)
            {
                string base = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
                string acc = save[i].getname() + "-" + save[i].getpass() + ".txt";
                fs::path accpath = fs::path(base) / acc;
                if (filesystem::exists(accpath))
                {
                    filesystem::remove(accpath);
                    cout << "Tai khoan da duoc khoa thanh cong\n";
                    return;
                }
                else
                {
                    cout << "Khong tim thay tai khoan, xin chu nhan thuc hien lai\n";
                    return erase();
                }
            }
        }
    }
}
