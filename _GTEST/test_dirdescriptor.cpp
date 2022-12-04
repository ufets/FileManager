#include "gtest/gtest.h"
#include "../SystemSource/User.hpp"
#include "../Descriptors/DirDescriptor.hpp"
TEST(DirDescriptor, constructor)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    cout<<current_path()<<"/root";
    std::cout<<"result:"<<create_directory(current_path()/"root");
}

TEST(DirDescriptor, create_subdir)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    cout<<current_path()<<"/root";
    FileDescriptor file("test", ".txt", admin, ALL);
    DirDescriptor subdir("subdir", ".dir", admin, ALL);
    create_directory(current_path()/"root");
   // root.create_(file, admin);
    root.create_(subdir, admin);
}

TEST(DirDescriptor, create_subfile)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    cout<<current_path()<<"/root";
    FileDescriptor file("test", ".txt", admin, ALL);
    DirDescriptor subdir("subdir", ".dir", admin, ALL);
    create_directory(current_path()/"root");
    root.create_(file, admin);
}

TEST(DirDescriptor, create_subfile_in_subdir)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    cout<<current_path()<<"/root";
    FileDescriptor file("test", ".txt", admin, ALL);
    DirDescriptor subdir("subdir", ".dir", admin, ALL);
    create_directory(current_path()/"root");
    root.create_(subdir, admin);
    DirDescriptor& mysubdir = root.open_subdir(subdir.get_name_extension(), admin);
    cout<<'w';
    mysubdir.get_path();
    mysubdir.create_(file, admin);
}