#include "gtest/gtest.h"
#include "../SystemSource/User.hpp"
#include "../SystemSource/SystemDescriptor.hpp"
#include "../Descriptors/AccessTable.hpp"

TEST(AccessTable, constructor)
{
    User user(1, "user", USER);
    AccessTable table(user);

    EXPECT_EQ(table.get_owner().get_id(), user.get_id());
    EXPECT_EQ(table.get_lvl(), OWNER);
}

TEST(AccessTable, add_user_no_matches)
{
    User user(1, "user", USER);
    AccessTable table(user);
    User newuser(2, "newuser", USER);
    Rights own2(true, true);
    table.add_user(newuser.get_id(), own2);
    EXPECT_EQ(table.view_access_reading(newuser.get_id()), true);
    EXPECT_EQ(table.view_access_writing(newuser.get_id()), true);
}

TEST(AccessTable, add_user_with_matches)
{
    User user(1, "user", USER);
    AccessTable table(user);
    User newuser2(2, "newuser", USER);
    Rights own2(true, true);
    table.add_user(newuser2.get_id(), own2);

    ASSERT_ANY_THROW(table.add_user(newuser2.get_id(), own2));
}

TEST(AccessTable, delete_user_no_matches)
{
    User user(1, "user", USER);
    AccessTable table(user);
    User newuser(2, "newuser", USER);
    Rights own2(true, true);
    table.add_user(newuser.get_id(), own2);

    ASSERT_ANY_THROW(table.view_access_reading(1)); //id
}

TEST(AccessTable, set_new_rules)
{
    User user(1, "user", USER);
    AccessTable table(user);

    User newuser(2, "newuser", USER);
    Rights own2(true, true);
    table.add_user(newuser.get_id(), own2);

    table.set_new_rules(2, false, false);

    EXPECT_EQ(table.view_access_reading(2), false);
    EXPECT_EQ(table.view_access_writing(2), false);
}

TEST(AccessTable, set_new_rules_with_throw)
{
    User user(1, "user", USER);
    AccessTable table(user);

    ASSERT_ANY_THROW(table.set_new_rules(2, false, false));
}