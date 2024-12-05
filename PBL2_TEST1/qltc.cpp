#include "qltc.h"
qluser::qluser()
{
}

qluser::~qluser()
{
}

void qluser::inputuser()
{
    
    string name, password;
    cin.ignore();
    cout << "Nhap ten nguoi dung: ";
    getline(cin, name);
    cout << "Nhap mat khau: ";
    getline(cin, password);
    use.setname(name);
    use.setpassword(password);

}

void qluser::check()
{
    filename = use.getname() + "-" + use.getpass() + ".txt";
    cout << filename << endl;
    string folderPath = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    bool found = false;
    try
    {
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
        cout << "Loi khi truy cap du lieu: " << e.what() << endl;
        return;
    }
    if (found)
    {
        fs::path file = fs::path(folderPath) / filename;
        ifstream inputfile(file);
        if (!inputfile)
        {
            cout << "LOI!KHONG THE TRUY CAP DUOC DU LIEU\n";
            return;
        }
        else
        {
            inputfile.close();
        }
    }
    else
    {
        cout << "Khong the tim thay ten tai khoan hoac mat khau sai, vui long nhap lai!" << endl;
    }
}

void qluser::create()
{
    filename = use.getname() + "-" + use.getpass() + ".txt";
    string folder = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    if (!fs::exists(folder))
    {
        cout << "LOI" << std::endl;
        recheck = 0;
        return;
    }

    if (!fs::is_directory(folder))
    {
        cout << "OPP LOI" << std::endl;
        recheck = 0;
        return;
    }

    fs::path filepath = fs::path(folder) / filename;
    ofstream newfile(filepath);
    if (newfile.is_open())
    {
        cout << "Tao tai khoan thanh cong" << endl;
        recheck = 1;
        newfile.close();
    }
    else
    {
        cout << "Khong the tao tai khoan" << endl;
    }
}

void qluser::checkmanager()
{
    string manager1 = "Ba Vu Han My";
    string manager2 = "Dao Quan 102230042";
    string tmpsave = use.getname() + " " + use.getpass();
    if (tmpsave == manager1 || tmpsave == manager2)
    {
        cout << "Chao mung chu nhan quay tro lai\n";
        managercheck = 1;
    }
    else
        managercheck = 0;
}