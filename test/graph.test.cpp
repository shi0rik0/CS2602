#include "graph/DenseGraph.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(GraphTest, Test1) {
    DenseGraph<int> g(10);
    g.add_edge(0, 1, 0);
    g.add_edge(0,2,1);
    g.add_edge(1,2, 2);
    EXPECT_EQ(g.edge(1,2), 2);
    auto f = [](int x) {cout << x << endl;};
    g.dfs(0, f);

}