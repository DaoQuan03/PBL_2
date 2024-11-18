#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

class user
{
private:
    string username, password;
public:
  
    user(string="", string="");
    void setname();
    void setpassword();
    string getname();
    string getpass();
    
    ~user();
};

