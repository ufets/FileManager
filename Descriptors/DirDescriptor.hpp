#ifndef DIR_DESCRIPTOR_H
#define DIR_DESCRIPTOR_H

#pragma once

#include "Descriptor.hpp"
#include "FileDescriptor.hpp"
#include <filesystem>
#include <memory>

namespace fsys = filesystem;
using namespace fsys;

class DirectoryContents{
private:
    vector<std::unique_ptr<Descriptor>> descriptors;
public:
    Descriptor* get_descriptor(int i);
    int size() const;

    int find(const string& name_extension) const;
    void add_descriptor(FileDescriptor* des);
    void add_descriptor(class DirDescriptor* des);
    void delete_descriptor(const string& name_extension);
    void print_files() const;
    void print_subdirs() const;
    void print_all() const;
    vector<std::unique_ptr<Descriptor>>::iterator get_it_begin();
};



class DirDescriptor: public Descriptor{
private:
    path cur_path;
    DirectoryContents content;
public:
    DirDescriptor(string name_, string extension_, User& owner_, ACCESS_LEVELS access_lvl_)
    :  content(), Descriptor(name_, extension_, owner_, access_lvl_)
    {
        cur_path = current_path()/name;
    }
    path get_path() const;
    void set_path(path new_path);

    DirectoryContents& get_content(User& client);

    void create_(FileDescriptor* file, User& client);
    void create_(DirDescriptor* subdir, User& client);
    void delete_(const string& name, const string& extension, User &client);

    //void rename_file(string old_name, string cur_extension, string new_name);
    //void change_extension_file(string cur_name, string old_extension, string new_extension);
    void print_all(User& client);
    void print_files(User& client);
    void print_dirs(User& client);

    void open_file_r(User& user);
    void open_file_w(User& user);
    DirDescriptor* open_subdir(const string& name, User& user);

    //DirDescriptor& operator=(DirDescriptor& right);
};


#endif