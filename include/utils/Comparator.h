//
// Created by zsy on 2021/11/26.
//

#ifndef CLION_PROJ_COMPARATOR_H
#define CLION_PROJ_COMPARATOR_H

enum class CmpResult {
    Gt,
    Lt,
    Eq,
};

template <typename T>
struct DefaultCmp {
    enum {Gt, Lt, Eq};
    int operator()(const T& x1, const T& x2) {
        if (x1 < x2) {
            return Lt;
        } else if (x1 > x2) {
            return Gt;
        } else {
            return Eq;
        }
    }
};

#endif //CLION_PROJ_COMPARATOR_H
