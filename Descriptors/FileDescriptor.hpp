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

};


void readline(string& str);

#endif
