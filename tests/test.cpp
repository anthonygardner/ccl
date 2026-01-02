#include <gtest/gtest.h>

#include "mylib.hpp"

TEST(MylibTest, Hello) {
    EXPECT_EQ(mylib::hello(), "Hello, world!");
}