#include <gtest/gtest.h>
#include "../src/include/Travel.hpp"

TEST(TravelTest, sumTest) {
    EXPECT_EQ(3, sum(1, 2));
    EXPECT_EQ(5, sum(2, 3));
    EXPECT_EQ(7, sum(3, 4));
}

TEST(TravelTest, sumTest2) {
    EXPECT_EQ(3, sum(1, 2));
    EXPECT_EQ(5, sum(2, 3));
    EXPECT_EQ(7, sum(3, 4));
}