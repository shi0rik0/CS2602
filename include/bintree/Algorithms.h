//
// Created by zsy on 2021/11/26.
//

#ifndef CLION_PROJ_ALGORITHMS_H
#define CLION_PROJ_ALGORITHMS_H

#include "utils/Comparator.h"

#include <type_traits>

template <typename NodePtr>
NodePtr& find_min_node(NodePtr& node) {
    auto pp = &node;
    while ((*pp)->left != nullptr) {
        pp = &((*pp)->left);
    }
    return *pp;
}

template <typename T>
using add_const_ref_t = std::add_lvalue_reference_t<std::add_const_t<T>>;

template <typename NodePtr, typename Cmp=DefaultCmp<std::remove_pointer_t<NodePtr>::ElemType>>
NodePtr* find_node(NodePtr& node, add_const_ref_t<typename std::remove_pointer_t<NodePtr>::ElemType> x) {
    auto pp = &node;
    while (*pp != nullptr) {
        auto result = Cmp()(x, (*pp)->data);
        if (result == Cmp::Lt) {
            pp = &((*pp)->left);
        } else if (result == Cmp::Gt) {
            pp = &((*pp)->right);
        } else {
            return pp;
        }
    }
    return nullptr;
}



#endif //CLION_PROJ_ALGORITHMS_H
