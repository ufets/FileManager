
#ifndef INTERMEDIARY_H
#define INTERMEDIARY_H
#include <fstream>
#pragma once
enum ACCESS_LEVELS{
    ALL,
    USERS,
    OWNER,
    ADMINS,
    OWNER_ADMIN
};

struct AccessTable{
private:
    int* users_id;
    int num_of_users;
    bool** actions; // r, w, c, d
public:
    AccessTable();
};

int file_size(std::string filename);


#endif
