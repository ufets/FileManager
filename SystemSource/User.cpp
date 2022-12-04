#include "User.hpp"

/*User::User()
{
    role = READER;
    user_id = -1;
    nickname = "";
}*/

User::User(int user_id_, std::string nickname_, ROLE role_): user_id(-1), nickname("noname"), role(READER){
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

User::User() {
    user_id = -1;
    nickname = "noname";
    role = READER;
}

bool operator>(const User &user1, const User &user2) {
    if(user1.get_id() > user2.get_id())
        return true;
    else return false;
}

bool operator<(const User &user1, const User &user2) {
    if(user1.get_id() < user2.get_id())
        return true;
    else return false;
}
