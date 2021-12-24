#pragma once

#include "utils/Allocator.h"
#include "list/SeqList.h"
#include <functional>


// 使用所谓的“二次探测法”
template <typename T, typename Hash=std::hash<T>>
class ClosedHashTable final {
private:
    enum class Status { EMPTY = 0, ACTIVE, DELETED };
    Hash hash_func;

    Status* status_arr;
    T* data_arr;
    int size = 0;
    int size_with_deleted = 0;
    int capacity;

    void expand() {
        auto new_status_arr = alloc::allocate<Status>(capacity * 2);
        for (int i = 0; i < capacity * 2; ++i) {
            new_status_arr[i] = Status::EMPTY;
        }
        auto new_data_arr = alloc::allocate<T>(capacity * 2);
        for (int i = 0; i < capacity; ++i) {
            if (status_arr[i] == Status::ACTIVE) {
                int k = hash_func(data_arr[i]) % (capacity * 2);
                int j = 1;
                for (;;) {
                    if (new_status_arr[k] != Status::ACTIVE) {
                        alloc::construct(new_data_arr + k, data_arr[i]);
                        new_status_arr[k] = Status::ACTIVE;
                        break;
                    } else {
                        k = (k + j) % (capacity * 2);
                        j += 2;
                    }
                }
            }
        }
        alloc::deallocate(data_arr, capacity);
        alloc::deallocate(status_arr, capacity);
        data_arr = new_data_arr;
        status_arr = new_status_arr;
        capacity *= 2;
        size_with_deleted = size;
    }
public:
    explicit ClosedHashTable(int capacity_=256) : capacity(capacity_) {
        status_arr = alloc::allocate<Status>(capacity);
        for (int i = 0; i < capacity; ++i) {
            status_arr[i] = Status::EMPTY;
        }
        data_arr = alloc::allocate<T>(capacity);

    }
    ~ClosedHashTable() {
        for (int i = 0; i < capacity; ++i) {
            if (status_arr[i] == Status::ACTIVE) {
                alloc::destruct(data_arr + i);
            }
        }
        alloc::deallocate(status_arr, capacity);
        alloc::deallocate(data_arr, capacity);
    }
    // 注意，可以改变返回值x，但是不能改变hash(x)，这里没法强制检查
    T* find(const T& x) {
        int i = hash_func(x) % capacity;
        int j = 1;
        for (;;) {
            if (status_arr[i] == Status::EMPTY) {
                return nullptr;
            } else if (status_arr[i] == Status::ACTIVE && data_arr[i] == x) {
                return data_arr + i;
            } else {
                i = (i + j) % capacity;
                j += 2;
            }
        }
    }
    void insert(const T& x) {
        int i = hash_func(x) % capacity;
        int j = 1;
        for (;;) {
            if (status_arr[i] != Status::ACTIVE) {
                alloc::construct(data_arr + i, x);
                status_arr[i] = Status::ACTIVE;
                ++size;
                ++size_with_deleted;
                if (size_with_deleted > capacity / 2) {
                    expand();
                }
                return;
            } else {
                i = (i + j) % capacity;
                j += 2;
            }
        }
    }
    void remove(const T& x) {
        int i = hash_func(x) % capacity;
        int j = 1;
        for (;;) {
            if (status_arr[i] == Status::EMPTY) {
                // TODO: 抛出一个std::exception
                throw "Error!";
            } else if (status_arr[i] == Status::ACTIVE && data_arr[i] == x) {
                alloc::destruct(data_arr + i);
                status_arr[i] = Status::DELETED;
                --size;
                return;
            } else {
                i = (i + j) % capacity;
                j += 2;
            }
        }
    }
};

// TODO: 写一个开散列表
template <typename T, typename Hash>
class OpenHashTable {

};