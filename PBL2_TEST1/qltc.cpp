#include "qltc.h"

qluser::qluser() { }

qluser::~qluser() { }

void qluser::inputuser()
{
    string name;
    cin.ignore();

    cout << "\n==========================================\n";
    cout << "|               USER LOGIN               |\n";
    cout << "==========================================\n";
    cout << "Enter username: ";
    getline(cin, name);

    // Sử dụng phương thức nhập mật khẩu bảo mật
    use.setname(name);
    use.setpassword_secure();
}

void qluser::check()
{
    filename = use.getname() + "-" + use.getpass() + ".txt";
    cout << "\n==========================================\n";
    cout << "|            ACCOUNT CHECKING            |\n";
    cout << "==========================================\n";
    cout << "Checking for file: " << filename << endl;
    
    string folderPath = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";
    bool found = false;

    try
    {
        // Checking if the file exists
        for (const auto &entry : fs::directory_iterator(folderPath))
        {
            if (entry.is_regular_file())
            {
                if (entry.path().filename() == filename)
                {
                    found = true;
                    recheck = 1;
                    break;
                }
            }
        }
    }
    catch (const fs::filesystem_error &e)
    {
        cout << "\nError accessing data: " << e.what() << endl;
        return;
    }

    if (found)
    {
        fs::path file = fs::path(folderPath) / filename;
        ifstream inputfile(file);
        if (!inputfile)
        {
            cout << "\n==========================================\n";
            cout << "|       ERROR: CANNOT ACCESS DATA       |\n";
            cout << "==========================================\n";
            return;
        }
        else
        {
            inputfile.close();
            cout << "\n==========================================\n";
            cout << "|     Account found, login successful    |\n";
            cout << "==========================================\n";
        }
    }
    else
    {
        cout << "\n==========================================\n";
        cout << "|      ACCOUNT NOT FOUND, TRY AGAIN      |\n";
        cout << "==========================================\n";
    }
}

void qluser::create()
{
    filename = use.getname() + "-" + use.getpass() + ".txt";
    string folder = "C:\\Users\\Admin\\OneDrive - The University of Technology\\Visual Studio Code\\OOP_PBL2\\DATABASE";

    if (!fs::exists(folder))
    {
        cout << "\n==========================================\n";
        cout << "|       ERROR: DIRECTORY NOT FOUN        |\n";
        cout << "==========================================\n";
        recheck = 0;
        return;
    }

    if (!fs::is_directory(folder))
    {
        cout << "\n==========================================\n";
        cout << "|       ERROR: INVALID DIRECTORY         |\n";
        cout << "==========================================\n";
        recheck = 0;
        return;
    }

    fs::path filepath = fs::path(folder) / filename;
    ofstream newfile(filepath);
    
    if (newfile.is_open())
    {
        cout << "\n==========================================\n";
        cout << "|      ACCOUNT CREATED SUCCESSFULLY      |\n";
        cout << "==========================================\n";
        recheck = 1;
        newfile.close();
    }
    else
    {
        cout << "\n==========================================\n";
        cout << "|    ERROR: UNABLE TO CREATE ACCOUNT     |\n";
        cout << "==========================================\n";
    }
}

void qluser::checkmanager()
{
    string manager1 = "Ba Vu Han My";
    string manager2 = "Dao Quan 102230042";
    string tmpsave = use.getname() + " " + use.getpass();

    if (tmpsave == manager1 || tmpsave == manager2)
    {
        cout << "\n==========================================\n";
        cout << "|      Welcome back, administrator!      |\n";
        cout << "==========================================\n";
        managercheck = 1;
    }
    else
    {
        managercheck = 0;
    }
}