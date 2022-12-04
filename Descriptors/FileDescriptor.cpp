#include "FileDescriptor.hpp"

void FileDescriptor::open_to_read(User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");
    fstream f;
    f.open(name+file_extension, ios::in);
    if (!f.is_open())
        throw std::invalid_argument("File opening error!");
    string content;
    getline(f, content);
    cout<<content;
    f.close();
}

void readline(string& str)
{
    while(true)
    {
        string buf;
        getline(cin, buf);
        str += '\n';
        str += buf;
        if(cin.eof())
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            return;
        }

    }

}

void FileDescriptor::open_to_write(User &client) {
    if (!check_access_r(client))
        throw std::logic_error("No access to this file!");

    setlocale(LC_ALL, "Russian");

    fstream f;
    f.open("test.txt", ios::app);
    if (!f.is_open())
        throw std::invalid_argument("File opening error!");


    string content;
    //SetConsoleCP(1251);
    readline(content);
    //SetConsoleCP(866);

    f.seekg(0, ios::end);

    f.close();
}
