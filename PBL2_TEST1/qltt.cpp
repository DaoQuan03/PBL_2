#include "qltt.h"
#include <iostream>

void qltt::input()
{
    access.inputuser();
    access.checkmanager();
}

bool qltt::creacc()
{

    if (access.managercheck)
    {
        return 1;
    }
    else
    {
        access.create();
        if (access.recheck != 1)
            return creacc();
        else
            return 0;
    }
}

bool qltt::checkdata()
{
    if (access.managercheck)
    {
        return 1;
    }
    else
    {
        access.check();
        if (access.recheck != 1)
            return checkdata();
        else
            credata();
        return 0;
    }
}

bool qltt::isValidNumber(const string &s) // Check if the input string is a valid number or empty
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit); // if empty string, return false
                                                                // all_of(begin, end, condition): checks if all elements satisfy the condition
                                                                // ::isdigit: checks if a character is a number from 0-9
}

int qltt::safeStoi(const string &s)
{
    if (isValidNumber(s))
    {
        return stoi(s);
    }
    throw invalid_argument("Invalid number: " + s); // an exception used to notify that an invalid argument has been passed
}

void qltt::credata()
{
    if (access.recheck == 1)
    {
        thoigian tmstt, tmet;
        string input = access.filename;
        string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
        fs::path filepath = fs::path(foldername) / input;
        ifstream file(filepath);
        if (!file)
        {
            cout << "Cannot access data\n";
            return;
        }
        char check;
        file.get(check); // Get the first character to check if user event data exists in the file
        if (file.eof())  // Check if the pointer has reached the end
        {
            cout << "You have not created event information\n";
        }
        else
        {
            file.unget(); // If there is data, return the first character fetched earlier
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
                getline(ss, tmsave, '|');
                tmstt.second = safeStoi(tmsave);

                // Check if there are no more characters after assigning tmstt.second
                if (ss.rdbuf()->in_avail() != 0) // Check if there is data left in the stringstream buffer
                                                 // rdbuf(): a method of the stream object to get a pointer to its memory buffer
                                                 // in_avail(): checks how many bytes remain in the buffer before being passed to the stream object
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
    heapsort sort;
    sort.heapsorT(events);
}

void qltt::writedata()
{
    vector<string> savevector;
    string tmtieude, tmmota, tmyear, tmmonth, tmday, tmhour, tmminute, tmsecond, tmsave;
    thoigian tmstt, tmet;

    cout << "\n==========================================\n";
    cout << "|         SAVING EVENTS TO FILE         |\n";
    cout << "==========================================\n";

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
    string foldername = "C:\\10000hcode)))))\\OOP\\PBL2_TEST2\\DATABASE";
    fs::path filepath = fs::path(foldername) / input;

    ofstream file(filepath);

    if (file.is_open())
    {
        cout << "Saving data to: " << filepath << "\n";
        for (int i = 0; i < savevector.size(); i++)
        {
            file << savevector[i] << endl;
        }
        file.close();
        cout << "\n==========================================\n";
        cout << "|        EVENTS SAVED SUCCESSFULLY       |\n";
        cout << "==========================================\n\n";
    }
    else
    {
        cout << "\n==========================================\n";
        cout << "|        ERROR: Cannot access data       |\n";
        cout << "==========================================\n";
    }
}

void qltt::print()
{
    if (events.empty())
    {
        cout << "\n==========================================\n";
        cout << "|          NO EVENTS AVAILABLE           |\n";
        cout << "==========================================\n\n";
        return;
    }

    cout << "\n==========================================\n";
    cout << "|                EVENT LIST              |\n";
    cout << "==========================================\n\n";

    for (size_t i = 0; i < events.size(); ++i)
    {
        cout << "Event " << i + 1 << ":\n";
        cout << "------------------------------------------\n";
        cout << "| Title       : " << events[i].gettieude() << "\n";
        cout << "| Description : " << events[i].getmota() << "\n";
        cout << "| Start Time  : " << events[i].getstt() << "\n";

        // Display End Time if available
        if (events[i].getet().getday() > 0)
        {
            cout << "| End Time    : " << events[i].getet() << "\n";
        }
        else
        {
            cout << "| End Time    : Not specified\n";
        }

        cout << "------------------------------------------\n";
    }
}

void qltt::add()
{
    string tmtieude, tmmota;
    thoigian tmstartime, tmendtime;
    int choice;

    cout << "\n==========================================\n";
    cout << "|              ADD NEW EVENT             |\n";
    cout << "==========================================\n";
    printcalenda();

    cout << "\nEnter the title of the event (enter '-1' to return to menu): ";
    getline(cin, tmtieude);
    if (tmtieude == "-1")
        return;

    cout << "\nEnter the description of the event (enter '-1' to return to menu): ";
    getline(cin, tmmota);
    if (tmmota == "-1")
        return;

    cout << "\nEnter the start time of the event:\n";
    if (!tmstartime.setinput())
        return;
        
    cout << "\n==========================================\n";
    cout << "|              ADD END TIME?             |\n";
    cout << "==========================================\n";
    cout << "1. Yes        2. No\n";
    cout << "Your choice (enter '-1' to return to menu): ";
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

    // Final confirmation
    char confirm;
    cout << "\n==========================================\n";
    cout << "|        CONFIRM EVENT ADDITION?         |\n";
    cout << "==========================================\n";
    cout << "Are you sure you want to add this event? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
    {
        Event tmp(tmtieude, tmmota, tmstartime, tmendtime);
        events.push_back(tmp);

        cout << "\n==========================================\n";
        cout << "|       EVENT ADDED SUCCESSFULLY        |\n";
        cout << "==========================================\n\n";
    }
    else
    {
        cout << "\n==========================================\n";
        cout << "|         EVENT ADDITION CANCELED        |\n";
        cout << "==========================================\n\n";
    }
    heapsort sort;
    sort.heapsorT(events);
}

void qltt::erase()
{
    if (events.empty())
    {
        cout << "\n==========================================\n";
        cout << "|          NO EVENTS TO DELETE           |\n";
        cout << "==========================================\n\n";
        return;
    }

    cout << "\n==========================================\n";
    cout << "|           SELECT EVENT TO DELETE       |\n";
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

    cout << "\nEnter the number of the event to delete (enter -1 to return to menu): ";
    int index;
    cin >> index;

    if (index == -1)
        return;

    if (index < 1 || index > events.size())
    {
        cout << "\n==========================================\n";
        cout << "|             INVALID CHOICE             |\n";
        cout << "==========================================\n";
        return;
    }

    cout << "\n==========================================\n";
    cout << "|   CONFIRM DELETE EVENT:                |\n";
    cout << "| - Title       : " << events[index - 1].gettieude() << endl;
    cout << "| - Description : " << events[index - 1].getmota() << endl;
    cout << "| - Start time  : " << events[index - 1].getstt() << endl;
    cout << "| - End time    : " << events[index - 1].getet() << endl;
    cout << "==========================================\n";

    char confirm;
    cout << "Are you sure you want to delete this event? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
    {
        events.erase(events.begin() + index - 1);
        cout << "\n==========================================\n";
        cout << "|       EVENT DELETED SUCCESSFULLY       |\n";
        cout << "==========================================\n\n";
    }
    else
    {
        cout << "\n==========================================\n";
        cout << "|        DELETE ACTION CANCELED          |\n";
        cout << "==========================================\n\n";
    }
}

void qltt::fix()
{
    if (events.empty())
    {
        cout << "\n==========================================\n";
        cout << "|          NO EVENTS TO MODIFY           |\n";
        cout << "==========================================\n\n";
        return;
    }

    cout << "\n==========================================\n";
    cout << "|                EVENT LIST              |\n";
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

    cout << "\nEnter the number of the event to modify (enter -1 to return to menu): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == -1)
        return;

    if (choice < 1 || choice > events.size())
    {
        cout << "\n==========================================\n";
        cout << "|             INVALID CHOICE             |\n";
        cout << "==========================================\n";
        return;
    }

    Event &selectedEvent = events[choice - 1];
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

void qltt::countdown()
{
    if (events.empty())
    {
        cout << "\n==========================================\n";
        cout << "|        NO EVENTS TO COUNTDOWN          |\n";
        cout << "==========================================\n\n";
        return;
    }

    heapsort sort;
    sort.heapsorT(events);

    cout << "\n==========================================\n";
    cout << "|               EVENTS LIST              |\n";
    cout << "==========================================\n";

    for (int i = 0; i < events.size(); ++i)
    {
        cout << i + 1 << ". " << endl;
        cout << "- Title       : " << events[i].gettieude() << endl;
        cout << "- Description : " << events[i].getmota() << endl;
        cout << "- Start time  : " << events[i].getstt() << endl;
        cout << "------------------------------------------" << endl;
    }

    cout << "\nEnter the number of the event to countdown: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > events.size())
    {
        cout << "\n==========================================\n";
        cout << "|             INVALID CHOICE             |\n";
        cout << "==========================================\n";
        return;
    }

    thoigian currentTime = thoigian::getCurrentTime();
    thoigian eventTime = events[choice - 1].getstt();
    thoigian timeRemaining = currentTime.timeUntil(eventTime);

    cout << "\n==========================================\n";
    cout << "|        COUNTDOWN TO SELECTED EVENT     |\n";
    cout << "==========================================\n";
    cout << "Event Title      : " << events[choice - 1].gettieude() << endl;
    cout << "Event Start Time : " << eventTime << endl;
    cout << "Time Remaining   : " << timeRemaining.day << " days, "
         << timeRemaining.hour << " hours, "
         << timeRemaining.minute << " minutes, "
         << timeRemaining.second << " seconds." << endl;
    cout << "==========================================\n\n";
}

void qltt::printcalenda()
{
    int year = 2025;
    int stDay;
    int day = 1;
    int month = 1;
    int y = year - (month < 3);
    int m = month + (month < 3 ? 12 : 0);
    int k = y % 100;
    int j = y / 100;
    stDay = (day + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    string months[] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    for (int month = 0; month < 12; ++month)
    {
        int daysInMonth;
        switch (month + 1)
        {
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        case 2:
            daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
            break;
        default:
            daysInMonth = 31;
        }

        cout << "-----------------------------" << endl;
        cout << " " << months[month] << " " << year << endl;
        cout << "-----------------------------" << endl;
        cout << " Sun Mon Tue Wed Thu Fri Sat " << endl;

        int doweek;
        for (doweek = 0; doweek < stDay; ++doweek)
        {
            cout << "    ";
        }

        for (int day = 1; day <= daysInMonth; ++day)
        {
            cout << setw(4) << day;
            if (++doweek > 6)
            {
                cout << endl;
                doweek = 0;
            }
        }

        if (doweek != 0)
        {
            cout << endl;
        }

        stDay = doweek;
    }
}
