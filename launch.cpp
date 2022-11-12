#include "launch.hpp"

void start()
{
    srand(time(nullptr));
    string pwd;
    D::input_string(pwd, "Enter admin 's password:");
    SystemDescriptor sys(pwd);
    User you = D::authorization(sys);
    work(sys, you);
    MainMenu(sys, you);

}

void MainMenu(SystemDescriptor& sys, User& user)
{
    cout<<"||  MAIN MENU  ||";
    const char *msgs[] = {"0. Quit from system", "1. Back to workspace ", "2. Change user"};
    const int num_msgs = sizeof(msgs) / sizeof(msgs[0]);
    void (*func[])(SystemDescriptor&, User&) = {nullptr, work, change_user};
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