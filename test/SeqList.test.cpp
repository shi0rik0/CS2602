#include "list/SeqList.h"
#include <iostream>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

// Demonstrate some basic assertions.
TEST(SeqListTest, SimpleTest) {
    SeqList<int> list;
    for (int i = 0; i < 3; ++i) {
        list.push(i);
    }
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << endl;
    }
    EXPECT_EQ(list.to_string(), "{0, 1, 2}");
    EXPECT_EQ(list.end_ref(), 2);
    list.pop();
    EXPECT_EQ(list.end_ref(), 1);
    list.clear();
    EXPECT_EQ(list.get_length(), 0);
}