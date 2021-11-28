//
// Created by zsy on 2021/11/26.
//

#ifndef CLION_PROJ_KEYVALUEPAIR_H
#define CLION_PROJ_KEYVALUEPAIR_H

#include "utils/Comparator.h"

#include <type_traits>



template <typename Key, typename Value>
struct KeyValuePair {
    Key key;
    Value value;
};


#endif //CLION_PROJ_KEYVALUEPAIR_H
