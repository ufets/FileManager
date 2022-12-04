#include "Descriptor.hpp"

Descriptor::Descriptor(string name_, string extension_, User& owner_, ACCESS_LEVELS access_lvl_)
                    :date_cr(), owner(owner_), exception_table(owner){
    name = name_;
    file_extension = extension_;
    exception_table.get_lvl();
    size_of_file = 0;
    exception_table.set_access_level(access_lvl_);
    time(&date_cr);     //устанавливаем дату создания
    date_mod = date_cr;
}

bool Descriptor::check_access_r(User &client) const{
    if (client.get_id() == owner.get_id() || client.get_role() > exception_table.get_lvl())
        return true;
    if (client.get_role() == exception_table.get_lvl())
    {
        try{
            return exception_table.view_access_reading(client.get_id());
        }
        catch (std::invalid_argument& inv)
        {
            return true;
        }
    }
    try{
        return exception_table.view_access_reading(client.get_id());
    }
    catch (std::invalid_argument& inv)
    {
        return true;
    }
}

bool Descriptor::check_access_w(User &client) const{
    if (client.get_id() == owner.get_id() || client.get_role() > exception_table.get_lvl())
        return true;
    if (client.get_role() == exception_table.get_lvl())
    {
        try{
            return exception_table.view_access_writing(client.get_id());
        }
        catch (std::invalid_argument& inv)
        {
            return true;
        }
    }
    try{
        return exception_table.view_access_writing(client.get_id());
    }
    catch (std::invalid_argument& inv)
    {
        return true;
    }

}

//getters
string Descriptor::get_name() const{
        return name;
}
string Descriptor::get_extension() const{
    return file_extension;
}
string Descriptor::get_name_extension() const{
    return (name+file_extension);
}
User& Descriptor::get_owner() const {
    return owner;
}
ACCESS_LEVELS Descriptor::get_access_lvl() const{
    return exception_table.get_lvl();
}
AccessTable& Descriptor::get_exception_table() {
    return exception_table;
}
unsigned long Descriptor::get_size() const{
    return size_of_file;
}
time_t& Descriptor::get_date_cr(){
    return date_cr;
}
time_t& Descriptor::get_date_mod(){
    return date_mod;
}



//setters
void Descriptor::set_name(string new_name) {
    name = new_name;
}
void Descriptor::set_extension(string new_extension) {
    file_extension = new_extension;
}
void Descriptor::set_owner(User& new_owner) {
    owner = new_owner;
}
void Descriptor::set_access_lvl(ACCESS_LEVELS new_lvl) {
    exception_table.set_access_level(new_lvl);
}
void Descriptor::update_size() {
    //size_of_file = get_size_of_object();        // ???
}
void Descriptor::set_time_mod() {
    time(&date_mod);
}


