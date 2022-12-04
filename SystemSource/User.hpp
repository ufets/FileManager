#ifndef USER_H
#define USER_H
#include <iostream>

enum ROLE{
    READER, USER, ADMIN = 4
};


class User {
private:
    int user_id;
    std::string nickname;
    ROLE role;
public:
    explicit User();
    explicit User(int user_id_, std::string nickname_, ROLE role_);
    int get_id() const;
    std::string get_nickname() const;
    ROLE get_role() const;
    void set_id(int new_id);
    void set_nickname(std::string new_nickname);
    void set_role(ROLE new_role);
    friend bool operator>(const User& user1, const  User& user2 );
    friend bool operator<(const User& user1, const  User& user2 );
};


#endif
