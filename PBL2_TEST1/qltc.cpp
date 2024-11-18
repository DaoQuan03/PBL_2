#include "qltc.h"
qluser::qluser()
{

}

qluser::~qluser()
{
}

void qluser::check(user tmuse)
{
    
    string input = tmuse.getname() + " " + tmuse.getpass() + ".txt";
    string folderPath = "C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    bool found = false;
    try
    {
        for (const auto &entry : fs::directory_iterator(folderPath))
        {
            if (entry.is_regular_file())
            {
                if (entry.path().filename() == input)
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
        ifstream inputfile(input);
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

void qluser::create(user tmuse)
{
    string filename = tmuse.getname() + " " + tmuse.getpass() + ".txt";
    string folder ="C:\\10000hcode)))))\\OOP\\PBL2_TEST1\\DATABASE";
    if (!fs::exists(folder)) {
        std::cout << "LOI" << std::endl;
        recheck = 0;
        return;
    }

    if (!fs::is_directory(folder)) {
        std::cout << "OPP LOI" << std::endl;
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


