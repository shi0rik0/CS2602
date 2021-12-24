#include <iostream>

using namespace std;

const int MAX_LEN = 1000000;
int temp[MAX_LEN];
int cmp_times = 0;

template <typename It>
It divide(It start, It end) {
    auto size = end - start;
    cmp_times += size - 1;
    int count = 0; // < pivot 的元素个数
    for (int i = 1; i < size; ++i) {
        if (start[i] < start[0]) {
            ++count;
        }
    }
    temp[count] = start[0];
    int j = 0;
    int k = count + 1;
    for (int i = 1; i < size; ++i) {
        if (start[i] > start[0]) {
            temp[k] = start[i];
            ++k;
        } else {
            temp[j] = start[i];
            ++j;
        }
    }
    for (int i = 0; i < size; ++i) {
        start[i] = temp[i];
    }
    return start + count;
}

template <typename It>
void quick_sort(It start, It end) {
    if (end - start <= 1) {
        return;
    }
    It mid = divide(start, end);
    quick_sort(start, mid);
    quick_sort(mid+1, end);
}

int arr[MAX_LEN];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        arr[i] = m;
    }
    quick_sort(arr, arr + n);
    cout << cmp_times;
    return 0;
}