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