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
    user tmp;
    string tmpname, tmppass;
    cin.ignore();
    cout << "Nhap ten chu nhan muon: ";
    getline(cin, tmpname);
    cout << "Nhap mat khau chu nhan muon: ";
    getline(cin, tmppass);
    tmp.setname(tmpname);
    tmp.setpassword(tmppass);
    save.push_back(tmp);
    string folder = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    string filename = tmpname + "-" + tmppass + ".txt";
    if (!fs::exists(folder))
    {
        cout << "DATABASE da bi loi" << endl;
        fs::create_directory(folder);
    }
    else if (!fs::is_directory(folder))
    {
        cout << "Loi khi them 1 pham nhan" << endl;
        return;
    }

    fs::path namepath = fs::path(folder) / filename;
    ofstream newacc(namepath);
    if (newacc.is_open())
    {
        cout << "Chu nhan da them tai khoan thanh cong" << endl;
        newacc.close();
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
                    thoigian tmstt;
                    string input = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
                    fs::path filepath = fs::path(foldername) / input;
                    ifstream file(filepath);
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
                        cout << "Tai khoan nay chua co thong tin su kien\n";
                        return;
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
                            tmmota = tmsave;
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
                    }
                    cout << "Nhap thu tu su kien chu nhan muon sua\n";
                    int choice = 0;
                    cin >> choice;
                    Event &selectedEvent = events[choice - 1];
                    string tieude, mota;
                    thoigian startTime;
                    cin.ignore();
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

                    selectedEvent.setstt(startTime);
                    cout << "Da cap nhat thong tin su kien thanh cong.\n";
                    cout << startTime;
                    vector<string> savevector;
                    string tmtieude, tmmota, tmyear, tmmonth, tmday, tmhour, tmminute, tmsecond, tmsave;
                    thoigian tmpstt = selectedEvent.getstt();
                    for (int i = 0; i < events.size(); i++)
                    {
                        tmtieude = "Tieu de:" + events[i].gettieude();
                        tmmota = "Mo ta: " + events[i].getmota();
                        tmstt = events[i].getstt();
                        tmyear = to_string(tmpstt.getyear());
                        tmmonth = to_string(tmpstt.getmonth());
                        tmday = to_string(tmpstt.getday());
                        tmhour = to_string(tmpstt.gethour());
                        tmminute = to_string(tmpstt.getminute());
                        tmsecond = to_string(tmpstt.getsecond());
                        tmsave = tmtieude + "|" + tmmota + "|" + "THOI GIAN BAT DAU:" + tmday + "/" + tmmonth + "/" + tmyear + "-" + tmhour + ":" + tmminute + ":" + tmsecond;
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
        print();
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
