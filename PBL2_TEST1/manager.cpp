#include "manager.h"

manager::manager()
{
}

manager::~manager()
{
}

void manager::print()
{
    string basedata = "C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
    
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

    // Hiển thị tiêu đề
    cout << "\n==========================================\n";
    cout << "|       ADD NEW ACCOUNT - MANAGER        |\n";
    cout << "==========================================\n";

    // Nhập thông tin chủ tài khoản
    cout << "\nEnter the owner's name: ";
    getline(cin, tmpname);
    cout << "Enter the owner's password: ";
    getline(cin, tmppass);

    ustmp.setname(tmpname);
    ustmp.setpassword(tmppass);
    save.push_back(ustmp);

    // Kiểm tra và tạo thư mục cơ sở dữ liệu
    string base = "C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
    string accname = ustmp.getname() + "-" + ustmp.getpass() + ".txt";

    if (!fs::exists(base))
    {
        cout << "\n[ERROR]: DATABASE is corrupted. Creating directory...\n";
        fs::create_directory(base);
    }
    else if (!fs::is_directory(base))
    {
        cout << "\n[ERROR]: Error adding a new account\n";
        return;
    }

    // Tạo tệp tài khoản mới
    fs::path accpath = fs::path(base) / accname;
    ofstream newacc(accpath);

    if (newacc.is_open())
    {
        cout << "\n==========================================\n";
        cout << "|       ACCOUNT ADDED SUCCESSFULLY       |\n";
        cout << "==========================================\n";
        newacc.close();

        // Thêm sự kiện mới
        int choice;
        vector<Event> events;
        string tmtieude, tmmota;
        thoigian tmstartime, tmendtime;

        cout << "\n==========================================\n";
        cout << "|           ADD NEW EVENT               |\n";
        cout << "==========================================\n";

        cout << "\nEnter the title of the event (enter '-1' to return to menu): ";
        getline(cin, tmtieude);
        if (tmtieude == "-1")
            return;

        cout << "Enter the description of the event (enter '-1' to return to menu): ";
        getline(cin, tmmota);
        if (tmmota == "-1")
            return;

        cout << "\nEnter the start time of the event (dd/mm/yyyy-hh:mm:ss, enter '-1' to return to menu): ";
        if (!tmstartime.setinput())
            return;

        cout << "\n==========================================\n";
        cout << "|            ADD END TIME?              |\n";
        cout << "==========================================\n";
        cout << "1. Yes        2. No (enter '-1' to return to menu): ";
        cin >> choice;
        cin.ignore();
        if (choice == -1)
            return;

        if (choice == 1)
        {
            cout << "\nEnter the end time of the event:\n";
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
            tmsave = tmptieude + "|" + tmpmota + "|" + tmday + "/" + tmmonth + "/" + tmyear + "-" + tmhour + ":" + tmminute + ":" + tmsecond;

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
        string inputmp = ustmp.getname() + "-" + ustmp.getpass() + ".txt";
        string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
        fs::path filepath = fs::path(foldername) / inputmp;
        ofstream file(filepath);

        if (file.is_open())
        {
            for (const auto &line : savevector)
            {
                file << line << endl;
            }
            file.close();
            cout << "\n==========================================\n";
            cout << "|      EVENT ADDED SUCCESSFULLY         |\n";
            cout << "==========================================\n\n";
        }
        else
        {
            cout << "\n[ERROR]: Cannot access the data\n";
        }
    }
    else
    {
        cout << "\n[ERROR]: Account creation failed\n";
        return;
    }
}
bool manager::creacc(){return 1;}
bool manager::checkdata(){return 1;}
void manager::input(){}
void manager::fix()
{
    print();
    cout << "\n==========================================\n";
    cout << "|          USER ACCOUNT MODIFICATION     |\n";
    cout << "==========================================\n";

    cout << "Enter the index of the user account you want to change (enter 0 to exit): ";
    int choose;
    cin >> choose;
    cin.ignore();
    if (choose == 0) return;

    if (choose < 1 || choose > save.size())
    {
        cout << "\n==========================================\n";
        cout << "|            INVALID CHOICE              |\n";
        cout << "==========================================\n";
        return;
    }

    bool done = false;
    for (int i = 0; i < save.size(); i++)
    {
        if (i == choose - 1)
        {
            int choosen = -1;
            do
            {
                cout << "\n==========================================\n";
                cout << "|         WHAT WOULD YOU LIKE TO DO?     |\n";
                cout << "==========================================\n";
                cout << "1. Change username and password\n";
                cout << "2. Change user data\n";
                cout << "0. Exit\n";
                cout << "==========================================\n";
                cout << "Enter your choice: ";
                cin >> choosen;
                cin.ignore();

                string tmname, tmpass, tmpold, base, tmpnew;
                fs::path oldacc, newacc;
                switch (choosen)
                {
                case 1:
                    cout << "\n==========================================\n";
                    cout << "|    MODIFY USERNAME AND PASSWORD        |\n";
                    cout << "==========================================\n";
                    cout << "Enter the desired username: ";
                    getline(cin, tmname);
                    cout << "Enter the desired password: ";
                    getline(cin, tmpass);

                    tmpold = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    base = "C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
                    oldacc = fs::path(base) / tmpold;
                    tmpnew = save[i].getname() + "-" + save[i].getpass() + ".txt";
                    newacc = fs::path(base) / tmpnew;

                    save[i].setname(tmname);
                    save[i].setpassword(tmpass);

                    if (fs::exists(oldacc))
                    {
                        try
                        {
                            fs::rename(oldacc, newacc);
                            cout << "\n==========================================\n";
                            cout << "|      USER ACCOUNT UPDATED SUCCESSFULLY |\n";
                            cout << "==========================================\n";
                        }
                        catch (const std::exception &e)
                        {
                            cerr << "Error: " << e.what() << '\n';
                        }
                    }
                    else
                    {
                        cout << "\n==========================================\n";
                        cout << "|             FILE NOT FOUND            |\n";
                        cout << "==========================================\n";
                    }
                    break;

                case 2:
                {
                    vector<Event> events;
                    thoigian tmstt, tmet;
                    string tpname = save[i].getname(), tppass = save[i].getpass();
                    string input = tpname + "-" + tppass + ".txt";
                    string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
                    fs::path filepath = fs::path(foldername) / input;

                    ifstream file(filepath);
                    if (!file)
                    {
                        cout << "\n==========================================\n";
                        cout << "|         CANNOT ACCESS DATA             |\n";
                        cout << "==========================================\n";
                        return;
                    }

                    char check;
                    file.get(check);
                    if (file.eof())
                    {
                        cout << "\n==========================================\n";
                        cout << "|     THIS ACCOUNT HAS NO EVENTS         |\n";
                        cout << "==========================================\n";
                        return;
                    }
                    else
                    {
                        file.unget();
                        string line, tmtieude, tmmota;
                        while (getline(file, line))
                        {
                            stringstream ss(line);
                            getline(ss, tmtieude, '|');
                            getline(ss, tmmota, '|');
                            // parsing the date and time information...
                            // (continue as you already have)
                            Event tmp(tmtieude, tmmota, tmstt, tmet);
                            events.push_back(tmp);
                        }
                        file.close();
                    }

                    cout << "\n==========================================\n";
                    cout << "|           EVENT LIST                   |\n";
                    cout << "==========================================\n";
                    for (int i = 0; i < events.size(); ++i)
                    {
                        cout << i + 1 << ". " << endl;
                        cout << "- Title       : " << events[i].gettieude() << endl;
                        cout << "- Description : " << events[i].getmota() << endl;
                        cout << "- Start time  : " << events[i].getstt() << endl;
                        cout << "- End time    : " << events[i].getet() << endl;
                        cout << "------------------------------------------" << endl;
                    }

                    int eventChoice;
                    cout << "\nEnter the number of the event to modify (enter -1 to return): ";
                    cin >> eventChoice;
                    cin.ignore();
                    if (eventChoice == -1)
                        return;

                    if (eventChoice < 1 || eventChoice > events.size())
                    {
                        cout << "\n==========================================\n";
                        cout << "|             INVALID CHOICE             |\n";
                        cout << "==========================================\n";
                        return;
                    }

                    Event &selectedEvent = events[eventChoice - 1];
                    string title, description;
                    thoigian startTime, endTime;

                    cout << "\n==========================================\n";
                    cout << "|       MODIFYING SELECTED EVENT         |\n";
                    cout << "==========================================\n";
                    cout << "Current Title: " << selectedEvent.gettieude() << "\n";
                    cout << "Enter new title (leave blank to keep current, -1 to return): ";
                    getline(cin, title);
                    if (title == "-1")
                        return;
                    if (!title.empty())
                        selectedEvent.settieude(title);

                    cout << "Current Description: " << selectedEvent.getmota() << "\n";
                    cout << "Enter new description (leave blank to keep current, -1 to return): ";
                    getline(cin, description);
                    if (description == "-1")
                        return;
                    if (!description.empty())
                        selectedEvent.setmota(description);

                    cout << "Current Start Time: " << selectedEvent.getstt() << "\n";
                    cout << "Enter new start time (-1 to return):\n";
                    if (!startTime.setinput())
                        return;

                    int choose;
                    cout << "Do you want to modify the end time?\n";
                    cout << "1. Yes            2. No (leave current end time, -1 to return)\n";
                    cin >> choose;
                    cin.ignore();

                    if (choose == -1)
                        return;

                    if (choose == 1)
                    {
                        cout << "Enter new end time (-1 to return):\n";
                        if (!endTime.setinput())
                            return;
                        selectedEvent.setet(endTime);
                    }

                    selectedEvent.setstt(startTime);

                    cout << "\n==========================================\n";
                    cout << "|      EVENT MODIFIED SUCCESSFULLY       |\n";
                    cout << "==========================================\n\n";
                }
                break;

                case 0:
                    cout << "\n==========================================\n";
                    cout << "|          EXITING THE PROGRAM           |\n";
                    cout << "==========================================\n";
                    done = true;
                    break;

                default:
                    cout << "\n==========================================\n";
                    cout << "|             INVALID CHOICE             |\n";
                    cout << "==========================================\n";
                }
            } while (choosen != 0);

            if (done)
                break;
        }
    }
}
void manager::writedata(){}
void manager::countdown(){}

void manager::erase()
{
    cout << "\n==========================================\n";
    cout << "|               USER LIST                |\n";
    cout << "==========================================\n";
    print();
    
    cout << "\n==========================================\n";
    cout << "|       ENTER THE INDEX TO DELETE        |\n";
    cout << "==========================================\n";
    cout << "Enter the index of the account you want to delete (enter 0 to cancel): ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 0)
    {
        cout << "\n==========================================\n";
        cout << "|        CANCELLING DELETION             |\n";
        cout << "==========================================\n";
        return;
    }

    if (choice < 1 || choice > save.size())
    {
        cout << "\n==========================================\n";
        cout << "|          INVALID CHOICE, TRY AGAIN     |\n";
        cout << "==========================================\n";
        return erase();
    }

    string base ="C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
    string acc = save[choice - 1].getname() + "-" + save[choice - 1].getpass() + ".txt";
    fs::path accpath = fs::path(base) / acc;
    
    if (fs::exists(accpath))
    {
        try
        {
            fs::remove(accpath);
            cout << "\n==========================================\n";
            cout << "|      ACCOUNT DELETED SUCCESSFULLY      |\n";
            cout << "==========================================\n";
        }
        catch (const std::exception &e)
        {
            cerr << "Error deleting account: " << e.what() << "\n";
        }
    }
    else
    {
        cout << "\n==========================================\n";
        cout << "|          ACCOUNT NOT FOUND             |\n";
        cout << "==========================================\n";
        return erase();
    }
}