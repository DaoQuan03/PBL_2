#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <conio.h>

namespace fs = std::filesystem;
using namespace std;

class user
{
private:
    string username, password;

public:
    user(string = "", string = "");
    void setname(string);
    void setpassword(string);
    string getname();
    string getpass();
    ~user();

    void setpassword_secure();
};

#endif