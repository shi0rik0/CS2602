#include <algorithms/Sort.h>
#include "algorithms/MST.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(AlgorithmsTest, SortTest) {
    const int N = 10;
    int arr[N] = {5,4,3,2,1};
    quick_sort(arr, arr + N);
    for (auto i : arr) {
        cout << i << endl;
    }
}

constexpr unsigned long long operator "" _i(unsigned long long i) {
    return i - 1;
}

TEST(AlgorithmsTest, MstTest) {
    SparseGraph<int> g(6);
    g.add_edge(1_i, 2_i, 6);
    g.add_edge(1_i, 3_i, 1);
    g.add_edge(1_i, 4_i, 5);
    g.add_edge(2_i, 3_i, 5);
    g.add_edge(2_i, 5_i, 3);
    g.add_edge(3_i, 4_i, 5);
    g.add_edge(3_i, 5_i, 6);
    g.add_edge(3_i, 6_i, 4);
    g.add_edge(4_i, 6_i, 2);
    g.add_edge(5_i, 6_i, 6);
    kruskal(g);
}