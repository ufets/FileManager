#include "SystemDescriptor.hpp"


using namespace std;
SystemDescriptor::SystemDescriptor(string admin_pwd)
{
    User admin(0, "admin", ADMIN);
    //root = DirDescriptor();
    users.push_back(admin);
    hashes.push_back(hash(admin_pwd));
}

SystemDescriptor::SystemDescriptor(fsys::path& system_data) {
    fstream fs((system_data/"hashes.txt").string(), fstream::in);
    string str;
    int i = 0;
    while(!fs.eof())
    {
        getline(fs, str);
        if (!str.empty())
            hashes.push_back(str);
        i++;
        str = "";
    }
    fs.close();
    fstream fs1((system_data/"nicknames.txt").string(), fstream::in);
    fstream fs2((system_data/"other.txt").string(), fstream::in);
    i = 0;
    int id;
    ROLE role;
    User useless;
    while(fs2.read((char*)&id, sizeof(int)))
    {
        useless.set_id(id);
        getline(fs1, str);
        useless.set_nickname(str);
        fs2.read((char*)&role, sizeof(ROLE));
        useless.set_role(role);
        users.push_back(useless);
        useless.~User();
        i++;
        str.~string();
    }
    fs1.close();
    fs2.close();
}

string SystemDescriptor::hash(string& password) {
    return password;
}

void SystemDescriptor::check_i(int i) const
{
    if (i < 0 || i >= users.size())
    {
        throw invalid_argument("invalid i!");
    }
}

User& SystemDescriptor::get_user(int i)
{
    check_i(i);
    return users[i];
}



int SystemDescriptor::get_num_of_us() const
{
    return (int)users.size();
}

int SystemDescriptor::find_user(int id) const
{
    for(int i = 0; i < users.size(); i++)
    {
        if (id == users[i].get_id())
        {
            return i;
        }
    }
    return -1;
}

int SystemDescriptor::find_user(string& nickname) const
{
    for(int i = 0; i < users.size(); i++)
    {
        if (nickname == users[i].get_nickname())
        {
            return i;
        }
    }
    return -1;
}


void SystemDescriptor::add_user(int id, string nickname, ROLE role, string password)
{
    if (find_user(id) != -1 || find_user(nickname) != -1)
    {
        throw std::invalid_argument("SystemDescriptor.cpp :: "
                                    "add_user(int id, string nickname, ROLE role) :: USER ALREADY EXISTS");
    }
    User user(id, nickname, role);
    users.push_back(user);
    add_hash(password);
}

void SystemDescriptor::add_hash(string& password)
{
    hashes.push_back(hash(password));
}

bool SystemDescriptor::check_nickname(int i, string& nickname) const
{
    check_i(i);
    if (nickname == users[i].get_nickname())
        return true;
    return false;
}

bool SystemDescriptor::check_hash(int i, string& password) const
{
    check_i(i);
    if(hash(password) == hashes[i])
    {
        return true;
    }
    return false;
}

void SystemDescriptor::delete_user(int id) {
    int i = find_user(id);
    if (i == -1 )
    {
        throw std::invalid_argument("SystemDescriptor :: delete_user(int id) :: There is not user with this id");
    }
    vector<User>::iterator it;
    it = users.begin();
    users.erase(it + i);
    delete_hash(i);
}

void SystemDescriptor::delete_user(string nickname) {
    int i = find_user(nickname);
    if (i == -1 )
    {
        throw std::invalid_argument("SystemDescriptor :: delete_user(string nickname) :: There is not user with this nickname");
    }
    vector<User>::iterator it;
    it = users.begin();
    users.erase(it + i);
    delete_hash(i);
}

void SystemDescriptor::delete_hash(int i)
{
    vector<string>::iterator it;
    it = hashes.begin();
    hashes.erase(it+i);
}

void SystemDescriptor::change_password(int i, string& password) {
    vector<string>::iterator it;
    it = hashes.begin();
    hashes.erase(it+i);
    hashes.insert(it+i, hash(password));
}

void SystemDescriptor::change_role(int i, ROLE role) {
    users[i].set_role(role);
}

void SystemDescriptor::print_users() {
    for(int i = 0; i < users.size(); i++)
    {
        cout<<"USER["<<i<<"]\t"<<users[i].get_nickname();
        if(users[i].get_role() == READER)
        {
            cout<<"(READER)";
        }
        else if(users[i].get_role() == USER)
        {
            cout<<"(USER)";
        }
        else if(users[i].get_role() == ADMIN)
        {
            cout<<"(ADMIN)";
        }
        cout<<"\t"<<hashes[i]<<endl;
    }

}

string SystemDescriptor::get_hash(int i) const {
    check_i(i);
    return hashes[i];
}







