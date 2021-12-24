#include "utils/DefaultInit.h"
#include "utils/Allocator.h"
#include "utils/Random.h"

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

#include <iostream>
using namespace std;
template <typename T>
void f(const T& x) {
    cout << "f1" << endl;
}

template <typename T>
struct S {

};

template <typename T>
void f(const S<T>& x) {
    cout << "f2" << endl;
}


TEST(UtilsTest, BasicTest2) {
    int i = 0;
    S<int> obj;
    f(i);
    f(obj);
}

TEST(UtilsTest, AllocatorTest) {
    auto p = alloc::allocate<int>(1);
    alloc::construct(p, 2);
    EXPECT_EQ(p[0], 2);
    alloc::destruct(p);
    alloc::deallocate(p, 1);
}

TEST(UtilsTest, RandomTest) {
    using namespace cs2602;
    auto g = RandomGenerator(666);
    for (int i = 0; i < 5; ++i) {
        cout << g.get(0, 9) << ' ' << g.get(0.0, 10.0) << endl;
    }
}