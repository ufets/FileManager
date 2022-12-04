#ifndef LAUNCH_H
#define LAUNCH_H

#include <iostream>
#include "../SystemSource/SystemDescriptor.hpp"
#include "../Dialog/Dialog.hpp"
#include <filesystem>
namespace fsys = std::filesystem;


void start();
void work(SystemDescriptor& sys, User& user);
void change_user(SystemDescriptor& sys,User& you);
void finish(SystemDescriptor& sys, User& you);
void MainMenu(SystemDescriptor& sys, User& user);

namespace mydata{
    void save_all(SystemDescriptor& sys, fsys::path& system_data);
    void write_hashes(SystemDescriptor& sys, fsys::path hashfile);
    void write_nicks(SystemDescriptor& sys, fsys::path nicksfile);
    void write_ids_roles(SystemDescriptor& sys, fsys::path otherfile);

}

#endif
