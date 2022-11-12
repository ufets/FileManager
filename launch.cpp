#include "launch.hpp"

void start()
{
    srand(time(nullptr));
    SystemDescriptor sys;
    User you = D::authorization(sys);
    work(you);

}

void work(User& you)
{
    cout<<"work!!!";
}