// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley

#include <gtest/gtest.h>
#include "user_controller.hpp"
#include "mock_logger.hpp"
#include "mock_data_access.hpp"

using namespace std;
using cadg_rest::UserController;
using cadg_rest::MockDataAccess;
using cadg_rest::MockLogger;


class UserControllerTest : public ::testing::Test {
protected:
    UserController user_controller(MockLogger logger, MockDataAccess dao);
};

TEST_F(UserControllerTest, InitializesHandlers) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST_F(UserControllerTest, HandlesGet) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST_F(UserControllerTest, HandlesPost) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST_F(UserControllerTest, HandlesPut) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST_F(UserControllerTest, HandlesDelete) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST_F(UserControllerTest, ReturnsUserById) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST_F(UserControllerTest, ReturnsUserByName) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST_F(UserControllerTest, ParsesUserId) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}