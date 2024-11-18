#include "User.h"


user::user(string name , string pass ) : username(name), password(pass)
{
}

user::~user()
{
}

void user::setname()
{
    cin.ignore();
    getline(cin, this->username);
}

void user::setpassword()
{
    getline(cin, this->password);
}

string user::getname()
{
    return this->username;
}

string user::getpass()
{
    return this->password;
}