#include "DirDescriptor.hpp"

int DirectoryContents::f_size() const
{
    return file_descriptors.size();
}

int DirectoryContents::d_size() const
{
    return dir_descriptors.size();
}

int DirectoryContents::f_find(const string& name_extension) const{
    for(int i = 0; i < file_descriptors.size(); i++)
    {
        if(file_descriptors[i].get_name_extension() == name_extension)
        {
            return i;
        }
    }
    return -1;
}

int DirectoryContents::d_find(const string& name_extension) const{
    for(int i = 0; i < dir_descriptors.size(); i++)
    {
        if(dir_descriptors[i].get_name_extension() == name_extension)
        {
            return i;
        }
    }
    return -1;
}

void DirectoryContents::add_f_descriptor(FileDescriptor& des) {
    file_descriptors.push_back(des);
}

void DirectoryContents::add_d_descriptor(DirDescriptor& des) {
    dir_descriptors.push_back(des);
}

void DirectoryContents::delete_d_descriptor(const string& name_extension) {
    int i = d_find(name_extension);
    if (i == -1 )
    {
        throw std::invalid_argument("Directory contents :: delete_descriptor :: There is no such descriptor!");
    }
    vector<DirDescriptor>::iterator it;
    it = dir_descriptors.begin();
    dir_descriptors.erase(it + i);
}

void DirectoryContents::delete_f_descriptor(const string& name_extension) {
    int i = f_find(name_extension);
    if (i == -1 )
    {
        throw std::invalid_argument("Directory contents :: delete_descriptor :: There is no such descriptor!");
    }
    vector<FileDescriptor>::iterator it;
    it = file_descriptors.begin();
    file_descriptors.erase(it + i);
}


void DirectoryContents::print_files() const{
    for(auto & descriptor : file_descriptors)
    {
            cout<<descriptor.get_name_extension()<<" ------- "<<descriptor.get_owner().get_nickname()
                <<"["<<descriptor.get_owner().get_role()<<"]"<<endl;
    }
}

void DirectoryContents::print_subdirs() const{
    for(auto & descriptor : dir_descriptors)
    {
            cout<<descriptor.get_name_extension()<<" ------- "<<descriptor.get_owner().get_nickname()
                <<"["<<descriptor.get_owner().get_role()<<"]"<<endl;
    }
}

void DirectoryContents::print_all() const{
    print_files();
    print_subdirs();
}

FileDescriptor& DirectoryContents::get_f_descriptor(int i) {
    return file_descriptors[i];
}

DirDescriptor& DirectoryContents::get_d_descriptor(int i) {
    return dir_descriptors[i];
}

vector<DirDescriptor>::iterator DirectoryContents::get_it_begin_d(){
    return dir_descriptors.begin();
}
vector<FileDescriptor>::iterator DirectoryContents::get_it_begin_f(){
    return file_descriptors.begin();
}


/*////////////////////////////////////////////////////////////////////////////////*/

path DirDescriptor::get_path() const{
    return cur_path;
}

void DirDescriptor::set_path(path& new_path){
    cur_path = new_path;
}

DirectoryContents &DirDescriptor::get_content(User &client) {
    if (!check_access_w(client))
        throw std::logic_error("No access to this directory!");
    return content;
}


void DirDescriptor::create_(FileDescriptor& file, User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    if ( content.f_find(file.get_name_extension())!=-1)
    {
        throw std::invalid_argument("Such object already exists!");
    }
    content.add_f_descriptor(file);
    fstream f;
    f.open((cur_path/file.get_name_extension()).string(), ios::out);
}

void DirDescriptor::create_(DirDescriptor& subdir, User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    if (content.d_find(subdir.get_name_extension()) != -1)
    {
        throw std::invalid_argument("Such object already exists!");
    }
    content.add_d_descriptor(subdir);
    create_directory(cur_path / subdir.get_name());
}

void DirDescriptor::delete_dir(string name_extension, User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    if(!exists(cur_path/name_extension))
    {
        throw std::invalid_argument("No such file or directory!");
    }
    content.delete_d_descriptor(name_extension);
    remove(cur_path/name_extension);
}

void DirDescriptor::delete_file(string name_extension, User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    if(!exists(cur_path/name_extension))
    {
        throw std::invalid_argument("No such file or directory!");
    }
    content.delete_f_descriptor(name_extension);
    remove(cur_path/name_extension);
}

void DirDescriptor::print_dirs(User& client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    content.print_subdirs();
}

void DirDescriptor::print_files(User& client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    content.print_files();
}

void DirDescriptor::print_all(User& client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this directory!");
    content.print_all();
}

DirDescriptor& DirDescriptor::open_subdir(string name_extension, User &client) {
    if(!check_access_r(client) || !check_access_w(client))
    {
        throw std::logic_error("No access to this directory!");
    }
    int i = content.d_find(name_extension);
    if (i == -1)
    {
        throw std::invalid_argument("No such file or directory!");
    }
    return (content.get_d_descriptor(i));
}
/*
DirDescriptor& DirDescriptor::operator=(DirDescriptor& right) {
    cur_path = right.cur_path;
    for(int i = 0; i < content.d_size(); i++)
    {
        content.delete_d_descriptor(content.get_d_descriptor(i).get_name_extension());
    }
    for(int i = 0; i < content.f_size(); i++)
    {
        content.delete_f_descriptor(content.get_f_descriptor(i).get_name_extension());
    }
    std::copy(right.content.get_it_begin_d(), right.content.get_it_end_d(), content.get_it_begin_d());

}
*/

