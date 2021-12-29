#include "graph/DenseGraph.h"
#include "graph/SparseGraph.h"
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

TEST(GraphTest, Test2) {
    SparseGraph<int> g(10);
    g.add_edge(0, 1, 0);
    g.add_edge(0,2,1);
    g.add_edge(1,2, 2);
//    auto f = [](int x) {cout << x << endl;};
//    g.dfs(0, f);
//    g.dijkstra(0);
    for (auto it = g.get_out_edge_begin_iterator(0); it != g.get_out_edge_end_iterator(0); ++it) {
        cout << it->to << ' ' << it->edge << endl;
    }
}