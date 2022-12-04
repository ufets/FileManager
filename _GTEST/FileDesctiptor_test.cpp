#include "gtest/gtest.h"
#include "../SystemSource/SystemDescriptor.hpp"
#include "../Descriptors/FileDescriptor.hpp"

TEST(FileDescritpor, open_to_read)
{
    User admin(1, "admin", ADMIN);
    FileDescriptor file("test", ".txt", admin, USERS);
    file.open_to_read(admin);
   // file.open_to_write(admin);
}
/*
TEST(FileDescritpor, open_to_write)
{
    User admin(1, "admin", ADMIN);
    FileDescriptor file("test", ".txt", admin, USERS);
    //file.open_to_read(admin);
    file.open_to_write(admin);
}*/