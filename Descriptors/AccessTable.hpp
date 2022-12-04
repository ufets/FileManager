
#include <fstream>
#include "../SystemSource/User.hpp"
#include <map>
#pragma once
enum ACCESS_LEVELS{
    ALL,
    USERS,
    OWNER,
    ADMINS,
};

struct Rights{
    bool r;
    bool w;
    explicit Rights(bool r_, bool w_):r(false), w(false){
        r = r_;
        w = w_;
    }
};

class AccessTable{
private:
    std::map<int, Rights> myMap;
    ACCESS_LEVELS access_lvl;
    User& owner;
public:
    explicit AccessTable(User& owner_):owner(owner_){
        access_lvl = OWNER;
    }
    User& get_owner();
    ACCESS_LEVELS get_lvl() const;
    void add_user(int user_id, Rights us);
    void delete_user(int user_id);
    bool view_access_reading(int user_id) const;
    bool view_access_writing(int user_id) const;
    void set_access_level(ACCESS_LEVELS new_lvl);
    void set_new_rules(int user_id, bool r_, bool w_);
    AccessTable& operator=(AccessTable right);
};

