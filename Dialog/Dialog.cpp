#include "Dialog.hpp"
#include "DActions.hpp"
using namespace std;



///проверяем строку на корректность
bool D::check_string(const string& str)
{
    char exc[]{'\"', ' ', '#', '%', '(', ')', '/', ',', ':', ';', '&', '+','-', '<', '>', '=', '*', '\\', '^', '`', '[', ']'};
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
        cout << "Incorrect password!";
        string str;
        D::input_string(str,"Enter 'register' to register, else enter smth another\n ---> "); // Проверка ввода
        if (str == "register")
        {
            break;
        }
    }while(true);
    return D::registration(sys);
}

User& D::registration(SystemDescriptor& sys)
{
    string nickname;
    string password;
    cout<<"|||     REGISTRATION    |||"<<endl;
    while(true){

        D::input_string(nickname, "Enter nickname: ");
        D::input_string(password, "Enter password: ");
        int flag = 0;
        for (int i = 0; i < sys.get_num_of_us(); i++) {
            if (sys.check_nickname(i, nickname)) {
                {   cout<<"System already has user with this nickname!"<<endl;
                    flag++;
                    break;
                }
            }
        }
        if (flag != 0) continue;
        int id = rand(); //generation unique id
        while(sys.find_user(id) != -1)
        {
            id = rand();
        }

        cout<<"your id = "<<id;
        sys.add_user(id, nickname, USER, password);
        return sys.get_user(sys.get_num_of_us() - 1);

    }
}

void D::Menu(SystemDescriptor& sys, User& user)
{
    const char *msgs[] = {"0. Quit", "1. Change password for smb", "2. Find user", "3. Open main dir",
                          "4. Create new user", "5. Delete user", "6. Print"};
    const int num_msgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*func[])(SystemDescriptor&, User&) = {nullptr, A::CHANGE_PASSWD, A::FIND_USER, A::OPEN_MAIN_DIR,
                                               A::CREATE_USER, A::DELETE_USER, A::PRINT};
    unsigned int rc;
    while (rc = D::Dialog(msgs, num_msgs)) {
        if (func[rc](sys, user) == R::EXIT) {
            break;
        }
    }
}

unsigned int D::Dialog(const char* msgs[], int num_msgs)
{
    unsigned int rc;
    std::cout<<"\n\n";
    for(int i = 0 ; i < num_msgs ; i++){
        std::cout<<"\n"<< msgs[i];
    }
    std::cout<<std::endl;
    do {
        D::get_value(rc);
        if ((rc >= 0) && (rc < num_msgs))
            return rc;
        std::cout<<"\nInvalid value!\n";
    }
    while(true);
}