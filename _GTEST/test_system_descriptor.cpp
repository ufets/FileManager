#include "gtest/gtest.h"
#include "../Launcher/launch.hpp"


TEST(SYSTEM_D, Constructor)
{
    SystemDescriptor sys("admin111");
    EXPECT_EQ(1, sys.get_num_of_us()); //our admin
    User admin = sys.get_user(0);
    EXPECT_EQ("admin", admin.get_nickname());
    std::string pwd = "admin111";
    EXPECT_EQ(true, sys.check_hash(0, pwd));
    EXPECT_EQ(ADMIN, admin.get_role());
}

TEST(SYSTEM_D, add_user)
{
    SystemDescriptor sys("admin111");
    sys.add_user(777, "user1", USER, "pwduser1");
    sys.add_user(776, "user2", USER, "pwduser2");
    EXPECT_EQ(3, sys.get_num_of_us()); //our admin + two users
    User user = sys.get_user(1);
    EXPECT_EQ("user1", user.get_nickname());
    string pwd1 = "pwduser1";
    string pwd2 = "pwduser2";
    EXPECT_EQ(true, sys.check_hash(1, pwd1));
    EXPECT_EQ(USER, user.get_role());
    user = sys.get_user(2);
    EXPECT_EQ("user2", user.get_nickname());
    EXPECT_EQ(true, sys.check_hash(2, pwd2));
    EXPECT_EQ(USER, user.get_role());

}

TEST(SYSTEM_D, delete_user_id)
{
    SystemDescriptor sys("admin111");
    sys.add_user(777, "user1", USER, "pwduser1");
    sys.add_user(776, "user2", USER, "pwduser2");
    EXPECT_EQ(3, sys.get_num_of_us()); //our admin + two users
    sys.delete_user(777);

    User user = sys.get_user(1);
    EXPECT_EQ("user2", user.get_nickname());
    string pwd2 = "pwduser2";
    EXPECT_EQ(true, sys.check_hash(1, pwd2));
    EXPECT_EQ(USER, user.get_role());
}

TEST(SYSTEM_D, delete_user_nick)
{
    SystemDescriptor sys("admin111");
    sys.add_user(777, "user1", USER, "pwduser1");
    sys.add_user(776, "user2", USER, "pwduser2");
    EXPECT_EQ(3, sys.get_num_of_us()); //our admin + two users
    sys.delete_user("user1");

    User user = sys.get_user(1);
    EXPECT_EQ("user2", user.get_nickname());
    string pwd2 = "pwduser2";
    EXPECT_EQ(true, sys.check_hash(1, pwd2));
    EXPECT_EQ(USER, user.get_role());
}

TEST(SYSTEM_D, change_password_and_role)
{
    SystemDescriptor sys("admin111");
    sys.add_user(777, "user1", USER, "pwduser1");
    sys.add_user(776, "user2", USER, "pwduser2");
    string pwd = "newpasswd";
    sys.change_password(1,  pwd);
    EXPECT_EQ(true, sys.check_hash(1, pwd));

    sys.change_role(1, ADMIN);
    User user = sys.get_user(1);
    EXPECT_EQ(ADMIN, user.get_role());

}

TEST(SYSTEM_D, print)
{
    SystemDescriptor sys("admin111");
    sys.add_user(777, "user1", USER, "pwduser1");
    sys.add_user(776, "user2", USER, "pwduser2");
    sys.print_users();
    EXPECT_EQ(1, 1);
}
int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}