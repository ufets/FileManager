#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Launcher/launch.hpp"

using namespace sf;

int main()
{

    //start();
    User admin(1, "admin", ADMIN);
    FileDescriptor file("test", ".txt", admin, USERS);
    file.open_to_read(admin);
    file.open_to_write(admin);

    return 0;

}