
#include "gtest/gtest.h"
#include "../SystemSource/User.hpp"
#include "../Descriptors/Descriptor.hpp"
#include <ctime>

TEST(Descriptor, constructor)
{
    User user(1, "owner", USER);
    Descriptor des("biba", ".txt", user, OWNER);
    EXPECT_EQ(des.get_name(), "biba");
    EXPECT_EQ(des.get_extension(), ".txt");
    EXPECT_EQ(des.get_name_extension(), "biba.txt");
    EXPECT_EQ(des.get_owner().get_id(), user.get_id());
    EXPECT_EQ(des.get_size(), 0);
    EXPECT_EQ(des.get_access_lvl(), OWNER);
    EXPECT_EQ(des.get_exception_table().get_owner().get_id(), user.get_id());
    cout<<"date_cr:"<<ctime(&des.get_date_cr())<<std::endl;
    cout<<"date_mod:"<<ctime(&des.get_date_mod())<<std::endl;
}

TEST(Descriptor, setters_getters)
{
    User user(1, "owner", USER);
    Descriptor des("biba", ".txt", user, OWNER);

    des.set_name("aaa");
    des.set_extension(".webp");
    des.set_access_lvl(ADMINS);
    User admin(2, "admin", ADMIN);
    des.set_owner(admin);

    des.set_time_mod();
    time_t timep;
    time(&timep);
    EXPECT_EQ(des.get_date_mod(), timep);

    EXPECT_EQ(des.get_name(), "aaa");
    EXPECT_EQ(des.get_extension(), ".webp");
    EXPECT_EQ(des.get_name_extension(), "aaa.webp");
    EXPECT_EQ(des.get_owner().get_id(), admin.get_id());
    EXPECT_EQ(des.get_access_lvl(), ADMINS);
    EXPECT_EQ(des.get_exception_table().get_owner().get_id(), admin.get_id());
}