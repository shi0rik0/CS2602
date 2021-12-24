#include "set/BST.h"
#include "list/SeqList.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>

using namespace std;

// Demonstrate some basic assertions.
TEST(BSTTest, BasicTest) {
    SeqList<int> list;
    BST<int> bst;
    for (int i = 0; i < 10; ++i) {
        int n = rand();
        list.push(n);
        bst.add(n);
    }
    for (int i = 0; i < 10; ++i) {
        cout << bst.contain(list[i]) << endl;
    }

    for (int i = 0; i < 10; ++i) {
        bst.remove(list[i]);
        cout << bst.contain(list[i]) << endl;
    }
}
