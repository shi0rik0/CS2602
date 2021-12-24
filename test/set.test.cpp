#include "set/BST.h"
#include "set/AVLTree.h"
#include "set/HashTable.h"
#include "list/SeqList.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>

using namespace std;

// Demonstrate some basic assertions.
TEST(SetTest, BasicTest) {
    SeqList<int> list;
    AVLTree<int> bst;
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

TEST(SetTest, HashTableTest) {
    ClosedHashTable<int> table(5);
    for (int i = 0; i < 10; ++i) {
        table.insert(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*table.find(i), i);
    }
    for (int i = 0; i < 10; ++i) {
        table.remove(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(table.find(i), nullptr);
    }
    for (int i = 0; i < 10; ++i) {
        table.insert(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*table.find(i), i);
    }
}