#ifndef DIR_DESCRIPTOR_H
#define DIR_DESCRIPTOR_H

#pragma once

#include "Descriptor.hpp"
#include "FileDescriptor.hpp"
#include <filesystem>

namespace fsys = filesystem;
using namespace fsys;

class DirectoryContents{
private:
    vector<class DirDescriptor> dir_descriptors;
    vector<FileDescriptor> file_descriptors;
public:
    DirDescriptor& get_d_descriptor(int i);
    FileDescriptor& get_f_descriptor(int i);

    int f_size() const;
    int d_size() const;
    vector<DirDescriptor>::iterator get_it_begin_d();
    vector<DirDescriptor>::iterator get_it_end_d();
    vector<FileDescriptor>::iterator get_it_begin_f();
    vector<DirDescriptor>::iterator get_it_end_f();
    int d_find(const string& name_extension) const;
    int f_find(const string& name_extension) const;
    void add_d_descriptor(DirDescriptor& des);
    void add_f_descriptor(FileDescriptor& des);
    void delete_d_descriptor(const string& name_extension);
    void delete_f_descriptor(const string& name_extension);
    void print_files() const;
    void print_subdirs() const;
    void print_all() const;
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
    void set_path(path& new_path);

    DirectoryContents& get_content(User& client);

    void create_(FileDescriptor& file, User& client);
    void create_(DirDescriptor& subdir, User& client);
    void delete_dir(string name_extension, User &client);
    void delete_file(string name_extension, User &client);

    void rename_file(string old_name, string cur_extension, string new_name);
    void change_extension_file(string cur_name, string old_extension, string new_extension);
    void print_all(User& client);
    void print_files(User& client);
    void print_dirs(User& client);

    void open_file_r(User& user);
    void open_file_w(User& user);
    DirDescriptor& open_subdir(string name_extension, User& user);

    //DirDescriptor& operator=(DirDescriptor& right);
};


#endif