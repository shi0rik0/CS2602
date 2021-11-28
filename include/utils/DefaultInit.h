//
// Created by zsy on 2021/11/26.
//

#ifndef CLION_PROJ_DEFAULTINIT_H
#define CLION_PROJ_DEFAULTINIT_H

#include <type_traits>

template <typename T>
struct DefaultInit {
    template<typename U = T>
    explicit DefaultInit(std::enable_if_t<std::is_scalar<U>::value>* = nullptr) : val(T(0)) {}

    template<typename U = T>
    explicit DefaultInit(std::enable_if_t<!std::is_scalar<U>::value>* = nullptr) {}
    T val;
};

#endif //CLION_PROJ_DEFAULTINIT_H
