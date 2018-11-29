// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley

#include <gtest/gtest.h>
#include "data_access_object.hpp"
#include "logger.hpp"
#include "user_controller.hpp"
using cadg_rest::DataAccessObject;
using cadg_rest::Logger;
using cadg_rest::UserController;


class UserControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
//        UserController user_controller(Logger::Instance(), DataAccessObject::Instance());
    }
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