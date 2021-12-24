#include <iostream>
#include <functional>
#include <iterator>

using namespace std;


template <typename It, typename LessThan>
It divide(It start, It end) {
    --end;
    auto k = *start;
    auto less = LessThan();
    do {
        while (start != end && !less(*end, k)) {
            --end;
        }
        if (start != end) {
            *start = *end;
            ++start;
        }
        while (start != end && !less(k, *start)) {
            ++start;
        }
        if (start != end) {
            *end = *start;
            --end;
        }
    } while (start != end);
    *start = k;
    return start;
}

template <typename It, typename LessThan=std::less<typename std::iterator_traits<It>::value_type>>
void quick_sort(It start, It end) {
    if (end - start <= 1) {
        return;
    }
    It mid = divide<It, LessThan>(start, end);
    quick_sort<It, LessThan>(start, mid);
    quick_sort<It, LessThan>(mid+1, end);
}


const int MAX_N = 100002;

int arr1[MAX_N];
int arr2[MAX_N];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        int m;
        cin >> m;
        arr1[i] = m;
    }
    for (int i = 0; i < n; ++i){
        int m;
        cin >> m;
        arr2[i] = m;
    }
    quick_sort(arr1+0, arr1+n);
    quick_sort(arr2+0, arr2+n);
    long long max_ans = 0;
    long long min_ans = 0;
    for (int i = 0; i < n; ++i) {
        max_ans += static_cast<long long>(arr1[i]) * arr2[i];
        min_ans += static_cast<long long>(arr1[i]) * arr2[n-i-1];
    }
    cout << max_ans << ' ' << min_ans;
    return 0;
}