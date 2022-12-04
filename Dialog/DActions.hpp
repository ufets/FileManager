#ifndef DACTIONS_HPP
#define DACTIONS_HPP
#include "../SystemSource/SystemDescriptor.hpp"

namespace A{
    enum ERRORS{
        SUCCESS = 1,
        NO_RIGHTS = 2,
    };
    int CHANGE_PASSWD(SystemDescriptor& sys, User& user);
    int FIND_USER(SystemDescriptor& sys, User& user);
    int OPEN_MAIN_DIR(SystemDescriptor& sys, User& user);
    int CREATE_USER(SystemDescriptor& sys, User& user);
    int DELETE_USER(SystemDescriptor& sys, User& user);
    int PRINT(SystemDescriptor& sys, User& user);
}

#endif
