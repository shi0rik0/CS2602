#pragma once

#include <iterator>
#include <cstddef>

template <typename It>
It binary_search(It start, It end, const typename std::iterator_traits<It>::value_type& x) {
    // [low, high)
    std::size_t low = 0;
    std::size_t high = end - start;
    while (low < high) {
        std::size_t mid = (low + high) / 2;
        if (x == start[mid]) {
            return start + mid;
        } else if (x < start[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return end;
}