#ifndef DIALOG_H
#define DIALOG_H

#include <iostream>
#include <limits>
#include "SystemDescriptor.hpp"
#pragma once

using namespace std;
namespace D{
enum ERRORS
{
    OK,
    EOF_,
    INVALID_VALUE
};

    template <class T>
    ERRORS get_value(T& obj)
    {
        cin>>obj;
        if(std::cin.eof())
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            return EOF_;
        }
        if (std::cin.fail())
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            return INVALID_VALUE;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            return OK;
        }

    }
    bool check_string(const string& str);
    User& authorization(SystemDescriptor& sys);
    User& registration(SystemDescriptor sys);
    void input_string(string& str, const string& msg);

}
#endif
