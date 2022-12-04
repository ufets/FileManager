#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <iostream>
#include <vector>
//#include <windows.h>
#include <limits>

#include "Descriptor.hpp"
#pragma once

class FileDescriptor: public Descriptor{
public:
    FileDescriptor(string name_, string extension_, User& owner_, ACCESS_LEVELS access_lvl_)
                        : Descriptor(name_, extension_, owner_, access_lvl_){}

    void open_to_read(User& client);
    void open_to_write(User& client);

    FileDescriptor& operator=(const FileDescriptor& right){
        name = right.name;
        file_extension = right.file_extension;
        User& owner = right.owner;
        exception_table = right.exception_table;
        size_of_file = right.size_of_file;
        date_cr = right.date_cr;
        date_mod = right.date_mod;
        return *this;
    }
};


void readline(string& str);

#endif
