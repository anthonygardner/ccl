#include <gtest/gtest.h>

#include <ccl/ccl.hpp>

TEST(MyTest, Hello) {
    EXPECT_EQ(ccl::hello(), "Hello, world!");
}