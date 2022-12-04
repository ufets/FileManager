#include "DActions.hpp"
using namespace std;

int A::CHANGE_PASSWD(SystemDescriptor& sys, User& user){
    if (user.get_role() < ADMIN)
    {
        cout<<"Not enough rights\n";
        return A::NO_RIGHTS;
    }
    cout<<"CHANGE_PASSWD\n";
    return A::SUCCESS;
}

int A::FIND_USER(SystemDescriptor& sys, User& user){
    cout<<"FIND USER\n";
    return A::SUCCESS;
}

int A::OPEN_MAIN_DIR(SystemDescriptor& sys, User& user){
    cout<<"OPEN_MAIN_DIR\n";
    return A::SUCCESS;
}

int A::CREATE_USER(SystemDescriptor& sys, User& user){
    if (user.get_role() < ADMIN)
    {
        cout<<"Not enough rights\n";
        return A::NO_RIGHTS;
    }
    cout<<"CREATE_USER";
    return A::SUCCESS;
}

int A::DELETE_USER(SystemDescriptor& sys, User& user){
    if (user.get_role() < ADMIN)
    {
        cout<<"Not enough rights\n";
        return A::NO_RIGHTS;
    }
    cout<<"DELETE_USER";
    return A::SUCCESS;
}

int A::PRINT(SystemDescriptor& sys, User& user){

    sys.print_users();
    return A::SUCCESS;
}