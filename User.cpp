#include "User.hpp"

User::User(int user_id_, std::string nickname_, ROLE role_){
    user_id = user_id_;
    nickname = nickname_;
    role = role_;
}

int User::get_id() const
{
    return user_id;
}
std::string User::get_nickname() const
{
    return nickname;
}
ROLE User::get_role() const
{
    return role;
}

void User::set_id(int new_id)
{
    user_id = new_id;
}
void User::set_nickname(std::string new_nickname)
{
    nickname = new_nickname;
}
void User::set_role(ROLE new_role)
{
    role = new_role;
}