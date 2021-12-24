//
// Created by zsy on 2021/11/28.
//

#ifndef CLION_PROJ_SORT_H
#define CLION_PROJ_SORT_H

#include <functional>
#include <iterator>

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



#endif //CLION_PROJ_SORT_H
