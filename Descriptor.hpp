#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H
#include <iostream>
#include "intermediary.hpp"
#include "User.hpp"
#include <fstream>

using namespace std;

class Descriptor {
protected:
    string name;
    string file_extension; //расширение файла
    User& owner;
    ACCESS_LEVELS access_lvl;
    AccessTable  exception_table;
    unsigned long size_of_file;
    time_t date_cr;
    time_t date_mod;
public:
   /* Descriptor(string name_, string extension_, int owner_id_, ACCESS_LEVELS access_lvl_):
            name("New File"), file_extension(".txt"), owner_id(-1), access_lvl(ALL), size_of_file(0)
    {

    };*/


};
#endif
