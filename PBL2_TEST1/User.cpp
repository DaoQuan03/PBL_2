#include "User.h"

user::user(string name, string pass) : username(name), password(pass)
{
}

user::~user()
{
}

void user::setname(string tmp)
{
    this->username = tmp;
}

void user::setpassword(string tmp)
{
    this->password = tmp;
}

string user::getname()
{
    return this->username;
}

string user::getpass()
{
    return this->password;
}

void user::setpassword_secure()
{
    string pass;
    char ch;
    cout << "Enter password: ";
    while ((ch = _getch()) != '\r') { // '\r' là phím Enter
        if (ch == '\b') { // Xử lý phím Backspace
            if (!pass.empty()) {
                cout << "\b \b"; // Xóa ký tự cuối trên màn hình
                pass.pop_back();
            }
        } else {
            pass.push_back(ch);
            cout << '*'; // Hiển thị dấu '*'
        }
    }
    cout << endl;
    this->password = pass;
}