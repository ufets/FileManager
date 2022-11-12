#include "Dialog.hpp"
using namespace std;
//using namespace D;
///проверяем строку на корректность
bool D::check_string(const string& str)
{
    char exc[]{'\"', ' ', '#', '%', '(', ')', '/', ',', ':', '.', ';', '&', '+','-', '<', '>', '=', '*', '\\', '^', '`', '[', ']'};
    for(char i : str)
    {
        if(33 > i || i>122)
        {
            return false;
        }
        for(char c : exc)
        {
            if(i == c)
            {
                return false;
            }
        }
    }
    return true;
}

///полное считывание строки
void D::input_string(string& str, const string& msg)
{
    while(true)
    {
        cout<<msg;
        D::ERRORS e = D::get_value(str);
        if(e == D::EOF_)
        {
            continue;
        }
        if(e == D::INVALID_VALUE)
        {
            cout<<"Error of input!"<<endl;
            continue;
        }
        if(!check_string(str))
        {
            cout<<"Illegal characters!"<<endl;
            continue;
        }
        else
        {
            return;
        }
    }
}

User& D::authorization(SystemDescriptor& sys){
    string nickname;
    string password;
    do {
        cout<<"|||     AUTHORIZATION    |||"<<endl;
        input_string(nickname, "Enter nickname: ");
        input_string(password, "Enter password: ");

        for (int i = 0; i < sys.get_num_of_us(); i++) {
            if (sys.check_nickname(i, nickname) && sys.check_hash(i, password)) {
                return sys.get_user(i);
            }
        }
        cout << "Incorrect password! Register?(1)"<<endl;
        int i;
        D::get_value(i); // Проверка ввода
        if (i == 1)
        {
            break;
        }
    }while(true);
    return D::registration(sys);
}

User& D::registration(SystemDescriptor sys)
{
    string nickname;
    string password;
    cout<<"|||     REGISTRATION    |||"<<endl;
    while(true){

        D::input_string(nickname, "Enter nickname: ");
        D::input_string(password, "Enter password: ");

        for (int i = 0; i < sys.get_num_of_us(); i++) {
            if (sys.check_nickname(i, nickname)) {
                cout<<"System already has user with this nickname!"<<endl;
                continue;
            }
        }
        int id = rand();
        sys.add_user(id, password, USER);
        return sys.get_user(sys.get_num_of_us() - 1);

    }
}
