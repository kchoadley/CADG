// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley

#include <gtest/gtest.h>

TEST(ExampleTests, IsEqual) {
    ASSERT_EQ(42, 42);
    EXPECT_EQ("Hello, World!", "Hello, World!");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
