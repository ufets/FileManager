#ifndef SYSTEM_DESCRIPTOR_H
#define SYSTEM_DESCRIPTOR_H

#include <iostream>
#include "User.hpp"
#include <string>
#include <memory>
#include <vector>
#include "DirDescriptor.hpp"
#pragma once
using namespace std;

class SystemDescriptor{
private:
    vector<User> users; //
    vector<string> hashes;
    DirDescriptor root; //
    string hash(string password) const;

public:
    SystemDescriptor(); //
    //SystemDescriptor(FILE* info);
    int get_num_of_us() const; //
    User& get_user(int i); //

    void check_i(int i) const; //

    int find_user(int id) const; //
    int find_user(string nickname) const; //

    void add_user(int id, string nickname, ROLE role); //
    void add_hash(string password); //

    void delete_user(int id); //
    void delete_user(string nickname); //
    void delete_hash(int i); //

    bool check_hash( int i, string password) const; //
    bool check_nickname(int i, string nickname) const; //
    void change_password( int i, string password); //
    void change_role(int i, ROLE role); //

    void print_users();
};

#endif
