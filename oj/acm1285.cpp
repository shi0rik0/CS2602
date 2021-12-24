#include <iostream>

using namespace std;
int c = 1;
int n = 0;
int k = 0;

void test_merge_sort(int start, int end) {
    if (start + 1 == end || c == k) {
        return;
    }
    int mid = start + ((end - start) % 2 ? (end - start) / 2 + 1 : (end - start) / 2);
    c += 2;
    test_merge_sort(mid, end);
    test_merge_sort(start, mid);
}

void fake_merge_sort(int start, int end) {
    if (start + 1 == end) {
        cout << start + 1  << ' ';
        return;
    }
    if (c == k) {
        for (int i = start; i < end; ++i) {
            cout << i + 1 << ' ';
        }
        return;
    }
    int mid = start + ((end - start) % 2 ? (end - start) / 2 + 1 : (end - start) / 2);
    c += 2;
    fake_merge_sort(mid, end);
    fake_merge_sort(start, mid);
}

int main() {
    cin >> n >> k;
    if (k % 2 == 0) {
        cout << -1;
        return 0;
    }
    test_merge_sort(0, n);
    if (c != k) {
        cout << -1;
        return 0;
    }
    c = 1;
    fake_merge_sort(0, n);
    return 0;
}