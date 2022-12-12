#include "gtest/gtest.h"
#include "../SystemSource/User.hpp"
#include "../Descriptors/DirDescriptor.hpp"
TEST(DirDescriptor, constructor)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    std::cout<<"result:"<<create_directory(current_path()/"root");
}

TEST(DirDescriptor, create_subdir)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    FileDescriptor* file = new FileDescriptor("test", ".txt", admin, ALL);
    DirDescriptor* subdir = new DirDescriptor("subdir", ".dir", admin, ALL);
    create_directory(current_path()/"root");
    root.create_(file, admin);
    root.create_(subdir, admin);
    cout<<"finished\n";
}

TEST(DirDescriptor, create_subfile_in_subdir)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);

    FileDescriptor* file = new FileDescriptor("test", ".txt", admin, ALL);
    DirDescriptor* subdir = new DirDescriptor("subdir", ".dir", admin, ALL);
    create_directory(current_path()/"root");
    root.create_(subdir, admin);
    subdir->create_(file, admin);
    cout<<"\nfinished\n";
}

TEST(DirDescriptor, open_subdir)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    FileDescriptor* file = new FileDescriptor("test", ".txt", admin, ALL);
    DirDescriptor* subdir = new DirDescriptor("subdir", ".dir", admin, ALL);
    create_directory(current_path()/"root");
    root.create_(subdir, admin);
    DirDescriptor* dir = root.open_subdir("subdir", admin);
    dir->create_(file, admin);
    cout<<"\nfinished\n";
}

TEST(DirDescriptor, rm_subdir)
{
    User admin(1, "admin", ADMIN);
    DirDescriptor root("root", ".dir", admin, ALL);
    FileDescriptor* file = new FileDescriptor("test", ".txt", admin, ALL);
    DirDescriptor* subdir = new DirDescriptor("subdir", ".dir", admin, ALL);
    create_directory(current_path()/"root");
    root.create_(subdir, admin);
    DirDescriptor* dir = root.open_subdir("subdir", admin);
    dir->create_(file, admin);
    root.delete_("subdir", ".dir", admin);
    cout<<"\nfinished\n";
}

