#include "DirDescriptor.hpp"

int DirectoryContents::size() const
{
    return (int)descriptors.size();
}


int DirectoryContents::find(const string& name_extension) const{
    for(int i = 0; i < descriptors.size(); i++)
    {
        if(descriptors[i].get()->get_name_extension() == name_extension)
        {
            return i;
        }
    }
    return -1;
}


void DirectoryContents::add_descriptor(FileDescriptor* des) {
    std::unique_ptr<Descriptor> ptr(des);
    descriptors.push_back(move(ptr));
}

void DirectoryContents::add_descriptor(DirDescriptor* des) {
    std::unique_ptr<Descriptor> ptr(des);
    descriptors.push_back(move(ptr));
}

void DirectoryContents::delete_descriptor(const string& name_extension) {
    int i = find(name_extension);
    if (i == -1 )
    {
        throw std::invalid_argument("Directory contents :: delete_descriptor :: There is no such descriptor!");
    }
    auto it = descriptors.begin();
    descriptors[i] = nullptr;
    descriptors.erase(it + i);
}




void DirectoryContents::print_files() const{
    for(const auto & descriptor : descriptors)
    {
        if(descriptor->get_extension() != ".dir"){
            cout<<descriptor->get_name_extension()<<" ------- "<<descriptor->get_owner().get_nickname()
                <<"["<<descriptor->get_owner().get_role()<<"]"<<endl;
        }

    }
}

void DirectoryContents::print_subdirs() const{
    for(const auto & descriptor : descriptors)
    {
        if(descriptor->get_extension() == ".dir"){
            cout<<descriptor->get_name_extension()<<" ------- "<<descriptor->get_owner().get_nickname()
                <<"["<<descriptor->get_owner().get_role()<<"]"<<endl;
        }

    }
}

void DirectoryContents::print_all() const{
    print_files();
    print_subdirs();
}

Descriptor* DirectoryContents::get_descriptor(int i) {
    return descriptors[i].get();
}


vector<std::unique_ptr<Descriptor>>::iterator DirectoryContents::get_it_begin(){
    return descriptors.begin();
}


/*////////////////////////////////////////////////////////////////////////////////*/


path DirDescriptor::get_path() const{
    return cur_path;
}

void DirDescriptor::set_path(path new_path){
    cur_path = new_path;
}

DirectoryContents &DirDescriptor::get_content(User &client) {
    if (!check_access_w(client))
        throw std::logic_error("No access to this directory!");
    return content;
}


void DirDescriptor::create_(FileDescriptor* file, User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    if ( content.find(file->get_name_extension())!=-1)
    {
        throw std::invalid_argument("Such object already exists!");
    }
    content.add_descriptor(file);
    fstream f;
    f.open(cur_path/file->get_name_extension(), std::ios::out);
    f.close();
}

void DirDescriptor::create_(DirDescriptor* subdir, User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    if (content.find(subdir->get_name_extension()) != -1)
    {
        throw std::invalid_argument("Such object already exists!");
    }
    subdir -> set_path(cur_path / subdir->get_name());
    content.add_descriptor(subdir);
    create_directory(cur_path / subdir->get_name());
}


void DirDescriptor::delete_(const string& name, const string& extension, User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this object!");
    if (extension != ".dir")
    {
        if(!exists(cur_path/(name+extension)))
        {
            throw std::invalid_argument("No such file or directory!");
        }

        remove(cur_path/(name+extension));
    }
    else{
        if(!exists(cur_path/name))
        {
            throw std::invalid_argument("No such file or directory!");
        }
        remove_all(cur_path/name);
    }
    content.delete_descriptor(name + extension);
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

DirDescriptor* DirDescriptor::open_subdir(const string& name, User &client) {
    if(!check_access_r(client) || !check_access_w(client))
    {
        throw std::logic_error("No access to this directory!");
    }
    int i = content.find(name+".dir");
    if (i == -1)
    {
        throw std::invalid_argument("No such file or directory!");
    }
    DirDescriptor* tmp = (DirDescriptor*)(content.get_descriptor(i));
    if (!tmp->check_access_r(client) || !(tmp->check_access_w(client)))
    {
        throw std::logic_error("No access to this directory!");
    }
    return tmp;
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

