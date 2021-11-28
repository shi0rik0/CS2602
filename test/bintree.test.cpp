#include "bintree/Algorithms.h"
#include "bintree/BinaryTreeNode.h"

#include <gtest/gtest.h>

using namespace std;

// Demonstrate some basic assertions.
TEST(BinTreeTest, BasicTest) {
    BinaryTreeNode<int> node;
    node.data = 2;
    node.left = new BinaryTreeNode<int>();
    node.left->data = 1;
    node.right = new BinaryTreeNode<int>();
    node.right->data = 3;
    auto p = find_node(&node, 1);
    EXPECT_EQ((**p).data, 1);
}
