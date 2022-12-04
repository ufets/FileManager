#include "launch.hpp"
#include <fstream>

using namespace fsys;
void start()
{
    srand(time(nullptr));
    string pwd;
    path system_data = "system data";
    if (exists(system_data / "nicknames.txt") && exists(system_data / "hashes.txt") //если есть файлы с прошлой работы
                                && exists(system_data / "other.txt"))
    {
        cout<<"LOADING...\n\n"<<endl;
        SystemDescriptor sys(system_data);
        User you = D::authorization(sys);
        work(sys, you);
        MainMenu(sys, you);
        finish(sys, you);
    }
    else{
        D::input_string(pwd, "Enter admin 's password:");       //их нет, создаем новую систему
        SystemDescriptor sys(pwd);
        User you = D::authorization(sys);
        work(sys, you);
        MainMenu(sys, you);
        finish(sys, you);
    }
    cout<<"BYE BYE!";
}

void MainMenu(SystemDescriptor& sys, User& user)
{
    cout<<"||  MAIN MENU  ||";
    const char *msgs[] = {"0. Quit from system", "1. Back to workspace ", "2. Change user"};
    const int num_msgs = sizeof(msgs) / sizeof(msgs[0]);
    void (*func[])(SystemDescriptor&, User&) = {finish, work, change_user};
    unsigned int rc;
    while (rc = D::Dialog(msgs, num_msgs))
    {
            func[rc](sys, user);
    }

}

void work( SystemDescriptor& sys, User& you)
{
    D::Menu(sys, you);
}

void change_user(SystemDescriptor& sys,User& you){
    you = D::authorization(sys);
    work(sys, you);
}

void finish(SystemDescriptor& sys, User& you){

    path system_data = "system data";
    if (!exists(system_data))
    {
        create_directory(system_data);
    }

    mydata::save_all(sys, system_data);
}


void mydata::save_all(SystemDescriptor& sys, path& system_data)
{
    write_nicks(sys, system_data/"nicknames.txt");
    write_hashes(sys, system_data/"hashes.txt");
    write_ids_roles(sys, system_data/"other.txt");
}

void mydata::write_hashes(SystemDescriptor& sys, path hashfile)
{
    fstream fs(hashfile.string(), fstream::out);
    for(int i = 0; i < sys.get_num_of_us(); i++)
    {
        fs<<sys.get_hash(i)<<"\n";
    }
    fs.close();
}

void mydata::write_nicks(SystemDescriptor& sys, path nicksfile)
{
    fstream fs(nicksfile.string(), fstream::out);
    for(int i = 0; i < sys.get_num_of_us(); i++)
    {
        fs<<sys.get_user(i).get_nickname()<<"\n";
    }
    fs.close();
}

void mydata::write_ids_roles(SystemDescriptor& sys, path otherfile)
{
    fstream fs(otherfile.string(), fstream::out);
    for(int i = 0; i < sys.get_num_of_us(); i++)
    {
        int id = sys.get_user(i).get_id();
        ROLE role = sys.get_user(i).get_role();
        fs.write((char*)&id, sizeof(int));
        fs.write((char*)&role, sizeof(ROLE));
    }
    fs.close();
}
