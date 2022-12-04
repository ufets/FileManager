#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H
#include <iostream>
#include "AccessTable.hpp"
#include "../SystemSource/User.hpp"
#include <fstream>

using namespace std;

class Descriptor {
protected:
    string name;
    string file_extension;
    User& owner;
    AccessTable  exception_table;
    unsigned long size_of_file;
    time_t date_cr;
    time_t date_mod;
public:
    Descriptor(string name_, string extension_, User& owner_, ACCESS_LEVELS access_lvl_);
    bool check_access_r(User& client) const;
    bool check_access_w(User &client) const;

    string get_name() const;
    string get_extension() const;
    string get_name_extension() const;
    User& get_owner() const;
    ACCESS_LEVELS get_access_lvl() const;
    AccessTable& get_exception_table();
    unsigned long get_size() const;
    time_t& get_date_cr();
    time_t& get_date_mod();

    void set_name(string new_name);
    void set_extension(string new_extension);
    void set_owner(User& new_owner);
    void set_access_lvl(ACCESS_LEVELS new_lvl);
    void update_size();
    void set_time_mod();

};


#endif
