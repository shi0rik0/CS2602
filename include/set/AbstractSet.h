//
// Created by zsy on 2021/11/25.
//

#ifndef CLION_PROJ_SET_H
#define CLION_PROJ_SET_H

template <typename T>
class AbstractSet {
public:
    virtual int get_size() const = 0;
    virtual bool contain(const T& x) const = 0;
    virtual bool add(const T& x) = 0;
    virtual bool remove(const T& x) = 0;
    virtual ~AbstractSet() {}
};

#endif //CLION_PROJ_SET_H
