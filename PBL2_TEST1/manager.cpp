#include "manager.h"

manager::manager()
{
}

manager::~manager()
{
}

void manager::print()
{
    string basedata = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
    
    // Đầu ra bắt đầu
    cout << "\n==========================================\n";
    cout << "|           USER LIST - MANAGER          |\n";
    cout << "==========================================\n";

    try
    {
        if (fs::exists(basedata) && fs::is_directory(basedata))
        {
            int i = 0;
            user use;
            string tmp, tmname, tmpass;
            
            // Lặp qua thư mục để hiển thị danh sách người dùng
            for (const auto &it : fs::directory_iterator(basedata))
            {
                cout << "\nUser " << i + 1 << ":\n";
                cout << "------------------------------------------\n";
                
                cout << "- Filename   : " << it.path().filename().string() << endl;
                
                tmp = it.path().filename().string();
                stringstream ss(tmp);
                getline(ss, tmname, '-');
                use.setname(tmname);
                getline(ss, tmpass, '.');
                use.setpassword(tmpass);
                save.push_back(use);

                cout << "- Username   : " << use.getname() << endl;
                cout << "- Password   : " << use.getpass() << endl;
                cout << "------------------------------------------\n";
                i++;
            }

            // Nếu không tìm thấy người dùng
            if (i == 0)
            {
                cout << "\n==========================================\n";
                cout << "|    No users found in the directory     |\n";
                cout << "==========================================\n";
            }
        }
        else
        {
            cout << "\n==========================================\n";
            cout << "|    ERROR: Unable to access data        |\n";
            cout << "==========================================\n";
        }
    }
    catch (const std::exception &e)
    {
        cout << "\n==========================================\n";
        cout << "|    ERROR: Cannot access the data       |\n";
        cout << "==========================================\n";
        std::cerr << "Error: " << e.what() << '\n';
    }
}


void manager::add()
{
    user ustmp;
    string tmpname, tmppass;
    cin.ignore();

    // Nhập thông tin chủ tài khoản
    cout << "\n==========================================\n";
    cout << "|       ADD NEW ACCOUNT - MANAGER        |\n";
    cout << "==========================================\n";

    cout << "Enter the owner's name: ";
    getline(cin, tmpname);
    cout << "Enter the owner's password: ";
    getline(cin, tmppass);

    ustmp.setname(tmpname);
    ustmp.setpassword(tmppass);
    save.push_back(ustmp);

    // Kiểm tra thư mục và tạo tài khoản
    string base = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
    string accname = ustmp.getname() + "-" + ustmp.getpass() + ".txt";
    
    if (!fs::exists(base))
    {
        cout << "\nERROR: DATABASE is corrupted. Creating directory...\n";
        fs::create_directory(base);
    }
    else if (!fs::is_directory(base))
    {
        cout << "\nERROR: Error adding a new account\n";
        return;
    }

    // Tạo tệp tài khoản mới
    fs::path accpath = fs::path(base) / accname;
    ofstream newacc(accpath);

    if (newacc.is_open())
    {
        cout << "\nAccount has been successfully added!\n";
        newacc.close();
        
        // Thêm sự kiện mới
        int choice;
        vector<Event> events;
        string tmtieude, tmmota;
        thoigian tmstartime, tmendtime;

        cout << "\nPlease add a new event for the account.\n";
        cout << "Enter title (enter -1 to go back to menu): ";
        getline(cin, tmtieude);
        if (tmtieude == "-1")
            return;

        cout << "Enter description (enter -1 to go back to menu): ";
        getline(cin, tmmota);
        if (tmmota == "-1")
            return;

        // Nhập thời gian bắt đầu sự kiện
        cout << "Enter start time (dd/mm/yyyy-hh:mm:ss, enter -1 to go back to menu): ";
        if (!tmstartime.setinput())
            return;

        cout << "Do you want to add an end time?\n";
        cout << "1. Yes            2. No (enter -1 to go back to menu)\n";
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

        // Lưu sự kiện vào tệp
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

        // Lưu thông tin vào tệp dữ liệu của tài khoản
        string inputmp = ustmp.getname() + "-" + ustmp.getpass() + "txt";
        string input = inputmp;
        string foldername = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
        fs::path filepath = fs::path(foldername) / input;
        ofstream file(filepath);

        if (file.is_open())
        {
            for (int i = 0; i < savevector.size(); i++)
            {
                file << savevector[i] << endl;
            }
            file.close();
            cout << "\nEvent successfully saved for this account.\n";
        }
        else
        {
            cout << "\nERROR: Cannot access the data\n";
        }
        return;
    }
    else
    {
        cout << "\nERROR: Account creation failed\n";
        return;
    }
}

void manager::fix()
{
    print();
    cout << "Enter the index of the user account you want to change\n"; // "Nhap so thu tu nguoi dung chu nhan muon thay doi"
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
                cout << "What do you want to do?\n"; // "Chu nhan muon toi thuc hien dieu gi~~"
                cout << "1. Change the username and password\n"; // "1. Thay doi ten va mat khau nguoi dung"
                cout << "2. Change user data\n"; // "2. Thay doi du lieu nguoi dung"
                cout << "0. Exit\n"; // "0. Thoat"
                cin >> choosen;
                cin.ignore();

                string tmname, tmpass, tmpold, base, tmpnew;
                fs::path oldacc, newacc;
                switch (choosen)
                {
                case 1:
                    cout << "Enter the desired username: "; // "Nhap ten chu nhan muon: "
                    getline(cin, tmname);
                    cout << "Enter the desired password: "; // "Nhap mat khau chu nhan muon: "
                    getline(cin, tmpass);
                    tmpold = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    cout << tmpold << endl;
                    save[i].setname(tmname);
                    save[i].setpassword(tmpass);
                    base = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
                    oldacc = fs::path(base) / tmpold;
                    tmpnew = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    newacc = fs::path(base) / tmpnew;

                    if (fs::exists(oldacc))
                    {
                        try
                        {
                            fs::rename(oldacc, newacc);
                            cout << "Congratulations, the user has been updated successfully\n"; // "Chuc mung chu nhan da thanh cong"
                        }
                        catch (const std::exception &e)
                        {
                            cerr << "Oops! An error occurred: " << e.what() << '\n'; // "OPP! A em da bi loi"
                        }
                    }
                    else
                    {
                        cout << "The base does not exist.\n"; // "Base khong ton tai."
                    }
                    break;
                case 2:
                {
                    vector<Event> events;
                    thoigian tmstt, tmet;
                    string tpname = save[i].getname(), tppass = save[i].getpass();
                    string input = tpname + "-" + tppass + ".txt";
                    cout << input << endl;
                    string foldername = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
                    fs::path filepath = fs::path(foldername) / input;
                    ifstream file(filepath);
                    if (!file)
                    {
                        cout << "Cannot access the data\n"; // "Khong the truy cap duoc du lieu"
                        return;
                    }
                    char check;
                    file.get(check);
                    if (file.eof())
                    {
                        cout << "This account has no event information\n"; // "Tai khoan nay chua co thong tin su kien"
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
                            // Check if there are no characters after assigning tmstt.second
                            if (ss.rdbuf()->in_avail() != 0) // Check if there is still data in the stringstream's buffer
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
                        cout << "No events to edit.\n"; // "Khong co su kien de chinh sua."
                        return;
                    }

                    cout << "Event list:\n"; // "Danh sach su kien:"
                    for (int i = 0; i < events.size(); ++i)
                    {
                        cout << i + 1 << ". " << endl;
                        cout << "- Title: " << events[i].gettieude() << endl; // "- Tieu de: "
                        cout << "- Description: " << events[i].getmota() << endl; // "- Mo ta: "
                        cout << "- Start: " << events[i].getstt() << endl; // "- Bat dau: "
                        cout << "- End: " << events[i].getet() << endl; // "- Ket thuc: "
                    }

                    int choice;
                    cout << "Enter the index of the event you want to edit (enter -1 to return to the menu): "; // "Nhap so thu tu cua su kien can chinh sua (nhap -1 de quay lai menu): "
                    cin >> choice;
                    cin.ignore();
                    if (choice == -1)
                        return;

                    if (choice < 1 || choice > events.size())
                    {
                        cout << "Invalid choice.\n"; // "Lua chon khong hop le."
                        return;
                    }

                    Event &selectedEvent = events[choice - 1];
                    string tieude, mota;
                    thoigian startTime, endTime;

                    cout << "Enter a new title (current title: " << selectedEvent.gettieude() << ", enter -1 to return): "; // "Nhap tieu de moi (tieu de hien tai: ..."
                    getline(cin, tieude);
                    if (tieude == "-1")
                        return;
                    if (!tieude.empty())
                    {
                        selectedEvent.settieude(tieude);
                    }

                    cout << "Enter a new description (current description: " << selectedEvent.getmota() << ", enter -1 to return): "; // "Nhap mo ta moi (mo ta hien tai: ..."
                    getline(cin, mota);
                    if (mota == "-1")
                        return;
                    if (!mota.empty())
                    {
                        selectedEvent.setmota(mota);
                    }

                    cout << "Enter a new start time (current start time: " << selectedEvent.getstt() << ", enter -1 to return): "; // "Nhap thoi gian bat dau moi (thoi gian hien tai: ..."
                    if (!startTime.setinput())
                        return;
                    int choose;
                    cout << "Do you want to add an end time?\n"; // "Ban co muon them thoi gian ket thuc khong?"
                    cout << "1. Yes            2. No (enter -1 to return to the menu)\n"; // "1. Co            2. Khong (nhap -1 de quay lai menu)"
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
                    cout << "Event information has been updated successfully.\n"; // "Da cap nhat thong tin su kien thanh cong."
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
                    string basename = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
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
                        cout << "Cannot access the data\n"; // "Khong the truy cap duoc du lieu"
                    }
                }
                break;
                case 0:
                    cout << "Exiting the program.\n"; // "Thoat chuong trinh."
                    done = true;
                    break;
                default:
                    cout << "Invalid choice, please choose again.\n"; // "Lua chon khong hop le, vui long chon lai."
                }
            } while (choosen != 0);
        }
        if (done)
            break;
    }
}

void manager::erase()
{
    cout << "User list: " << endl; // "Danh sach nguoi dung"
    print();
    cout << "Enter the index of the account you want to delete\n"; // "Nhap so thu tu tai khoan chu nhan muon xoa"
    int choice;
    cin >> choice;
    if (choice > save.size() - 1)
    {
        cout << "Your choice has exceeded the valid range, please try again\n"; // "Lua chon cua chu nhan da vuot qua so ke pham trong tran tuc, xin chu nhan nhap lai"
        return erase();
    }
    else
    {
        for (int i = 0; i < save.size() - 1; i++)
        {
            if (i == choice - 1)
            {
                string base = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
                string acc = save[i].getname() + "-" + save[i].getpass() + ".txt";
                fs::path accpath = fs::path(base) / acc;
                if (filesystem::exists(accpath))
                {
                    filesystem::remove(accpath);
                    cout << "The account has been successfully deleted\n"; // "Tai khoan da duoc khoa thanh cong"
                    return;
                }
                else
                {
                    cout << "Account not found, please try again\n"; // "Khong tim thay tai khoan, xin chu nhan thuc hien lai"
                    return erase();
                }
            }
        }
    }
}