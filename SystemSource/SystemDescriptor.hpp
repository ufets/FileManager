#ifndef SYSTEM_DESCRIPTOR_H
#define SYSTEM_DESCRIPTOR_H

#include <iostream>

#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <filesystem>


#include "../Descriptors/DirDescriptor.hpp"
#include "User.hpp"


#pragma once
using namespace std;
namespace fsys = filesystem;

class SystemDescriptor{
private:
    vector<User> users;
    vector<string> hashes;
    //DirDescriptor root;
    static string hash(string& password) ;

public:
    explicit SystemDescriptor(string admin_pwd);
    explicit SystemDescriptor(fsys::path& system_data);
    int get_num_of_us() const;
    string get_hash(int i) const;
    User& get_user(int i);

    void check_i(int i) const;

    int find_user(int id) const;
    int find_user(string& nickname) const;

    void add_user(int id, string nickname, ROLE role, string password);
    void add_hash(string& password);

    void delete_user(int id);
    void delete_user(string nickname);
    void delete_hash(int i);

    bool check_hash( int i, string& password) const;
    bool check_nickname(int i, string& nickname) const;
    void change_password( int i, string& password);
    void change_role(int i, ROLE role);

    void print_users();
};

#endif
