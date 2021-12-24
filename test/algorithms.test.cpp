#include <algorithms/Sort.h>
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