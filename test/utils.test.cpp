#include "utils/DefaultInit.h"

#include <gtest/gtest.h>

#include <vector>

using namespace std;

// Demonstrate some basic assertions.
TEST(UtilsTest, BasicTest) {
    enum Ok {NO=0, YES};
    DefaultInit<int> x1;
    EXPECT_EQ(x1.val, 0);
    DefaultInit<double> x2;
    EXPECT_EQ(x2.val, 0);
    DefaultInit<void*> x3;
    EXPECT_EQ(x3.val, nullptr);
    DefaultInit<vector<int>> x4;
    EXPECT_EQ(x4.val.empty(), true);
    DefaultInit<Ok> x5;
    EXPECT_EQ(x5.val, NO);
}
