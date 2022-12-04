#include "AccessTable.hpp"


User& AccessTable::get_owner() {
    return owner;
}

ACCESS_LEVELS AccessTable::get_lvl() const {
    return access_lvl;
}

void AccessTable::add_user(int user_id, Rights us)
{
    auto it = myMap.find(user_id);
    if(it != myMap.end() || user_id == owner.get_id())
    {
        throw std::invalid_argument("Access table::add_user:: such a user already exists");
    }
    myMap.emplace(user_id, us);
}

void AccessTable::delete_user(int user_id)
{
    auto it = myMap.find(user_id);
    if(it == myMap.end())
    {
        throw std::invalid_argument("Access table::delete_user::   no such user");
    }
    myMap.erase(it);
}


bool AccessTable::view_access_reading(int user_id) const {
    auto it = myMap.find(user_id);
    if(it == myMap.end())
    {
        throw std::invalid_argument("Access table::view_access_reading::   no such user");
    }
    return it -> second.r;
}

bool AccessTable::view_access_writing(int user_id) const {
    auto it = myMap.find(user_id);
    if(it == myMap.end())
    {
        throw std::invalid_argument("Access table::view_access_writing::   no such user");
    }
    return it -> second.w;
}

void AccessTable::set_access_level(ACCESS_LEVELS new_lvl)
{
    access_lvl = new_lvl;
}

void AccessTable::set_new_rules(int user_id, bool r_, bool w_)
{
    auto it = myMap.find(user_id);
    if(it == myMap.end())
    {
        throw std::invalid_argument("Access table::set_new_rules::   no such user");
    }
    it->second.r = r_;
    it->second.w = w_;
}

//NOT TESTED
AccessTable& AccessTable::operator=(AccessTable right) {
    owner = right.owner;
    access_lvl = right.access_lvl;

    auto it = myMap.begin();
    while(it != myMap.end()){
        myMap.erase(it);
    }

    auto it2 = right.myMap.begin();
    while(it2 != right.myMap.end())
    {
        add_user(it2->first, it2->second);
    }
    return (*this);
}


