#include "list/SeqList.h"

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(SeqListTest, SimpleTest) {
    SeqList<int> list;
    for (int i = 0; i < 3; ++i) {
        list.push(i);
    }
    EXPECT_EQ(list.get_test_string(), "{0, 1, 2}");
    EXPECT_EQ(list.end_ref(), 2);
    list.pop();
    EXPECT_EQ(list.end_ref(), 1);
    list.clear();
    EXPECT_EQ(list.get_length(), 0);
}