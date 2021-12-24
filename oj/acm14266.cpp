#include <iostream>
#include <iterator>

using namespace std;

const int MAX_LEN = 100005;
int arr[MAX_LEN];

template <typename It>
int binary_search(It start, It end, const typename std::iterator_traits<It>::value_type& x) {
    // [low, high)
    int low = 0;
    int high = end - start;
    while (low < high) {
        int mid = (low + high) / 2;
        if (x == start[mid]) {
            return mid;
        } else if (x < start[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        arr[i] = k;
    }
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        int j = binary_search(arr, arr + n, k);
        cout << (j < n ? arr[j] : -1) << endl;
    }
    return 0;
}
