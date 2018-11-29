// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley

#include <gtest/gtest.h>
#include "controller.hpp"

class ControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

};

TEST(ControllerTest, ReturnsEndpoint) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

TEST(ControllerTest, ReturnsQueries) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}
