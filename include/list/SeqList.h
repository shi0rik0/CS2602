#pragma once

#include <memory>
#include <tuple>
#include <functional>
#include <string>
#include <sstream>

// todo: 实现拷贝构造函数和赋值重载（好像有bug？）

template <typename T>
class SeqList final {
public:
    SeqList() : max_len(64) {
        data = alloc.allocate(max_len);
    }
    ~SeqList() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, max_len);
    }
    SeqList(const SeqList& other) {
        data = alloc.allocate(other.max_len);
        for (int i = 0; i < other.len; ++i) {
            alloc.construct(data + i, other.data[i]);
        }
        len = other.len;
        max_len = other.max_len;
    }
    SeqList& operator=(const SeqList<T>& other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, max_len);
        data = alloc.allocate(other.max_len);
        for (int i = 0; i < other.len; ++i) {
            alloc.construct(data + i, other.data[i]);
        }
        len = other.len;
        max_len = other.max_len;
        return *this;
    }
    void reserve(int capacity) {
        while (max_len < capacity) {
            double_space();
        }
    }
    int get_length() const {
        return len;
    }
    T& operator[](int i) {
        return data[i];
    }
    const T& operator[](int i) const {
        auto& r = *const_cast<SeqList*>(this);
        return r[i];
    }
    SeqList operator+(const SeqList& rhs) const {
        int new_len = len + rhs.len;
        SeqList r(new_len * 2);
        int i;
        for (i = 0; i < len; ++i) {
            r.alloc.construct(r.data + i, data[i]);
        }
        for (int j = 0; j < rhs.len; ++j) {
            r.alloc.construct(r.data + i + j, rhs.data[j]);
        }
        return r;
    }
    template <typename U>
    void splice(int i, int dn, const U& start, const U& end) {
        int in = end - start;
        int new_len = len - dn + in;
        while (max_len < new_len) {
            double_space();
        }
        if (dn < in) {
            for (int j = len - 1; j >= len - in + dn; --j) {
                alloc.construct(data + j + in - dn, data[j]);
            }
            for (int j = len - in + dn - 1; j >= i + dn; --j) {
                data[j + in - dn] = data[j];
            }
        } else {
            for (int j = i + dn; j < len; ++j) {
                data[j + in - dn] = data[j];
            }
            for (int j = new_len; j < len; ++j) {
                alloc.destroy(data + j);
            }
        }
        for (int j = 0; j < in; ++j) {
            data[i + j] = start[j];
        }
        len = new_len;
    }
    void insert(int i, const T& e) {
        if (len == max_len) {
            double_space();
        }
        alloc.construct(data + len, data[len - 1]);
        for (int j = len - 2; j >= i; --j) {
            data[j + 1] = data[j];
        }
        data[i] = e;
        ++len;
    }
    void remove(int i) {
        for (int j = i + 1; j < len; ++j) {
            data[j - 1] = data[j];
        }
        alloc.destroy(data + len - 1);
        --len;
    }
    T &end_ref() {
        return data[len - 1];
    }
    const T&end_ref() const {
        auto& r = *const_cast<SeqList*>(this);
        return r.end_ref();
    }
    void push(const T& e) {
        if (len == max_len) {
            double_space();
        }
        alloc.construct(data + len, e);
        ++len;
    }
    void pop() {
        alloc.destroy(data + len - 1);
        --len;
    }
    void clear() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        len = 0;
    }
    std::tuple<T*, int> find(const std::function<bool(const T&)>& func, int start=0) {
        for (int i = start; i < len; ++i) {
            if (func(data[i])) {
                return std::make_tuple(data + i, i);
            }
        }
        return std::make_tuple(nullptr, -1);
    }
    std::tuple<const T*, int> find(const std::function<bool(const T&)>& func, int start=0) const {
        auto& r = *const_cast<SeqList*>(this);
        return r.find(func, start);
    }
    std::string get_test_string() const {
        std::ostringstream oss;
        auto sep = "{";
        for (int i = 0; i < len; ++i) {
            oss << sep << data[i];
            sep = ", ";
        }
        oss << "}";
        return oss.str();
    }
private:
    T* data = nullptr;
    int len = 0;
    int max_len = 0;
    std::allocator<T> alloc;

    void double_space() {
        max_len *= 2;
        T* new_data = alloc.allocate(max_len);
        for (int i = 0; i < len; ++i) {
            alloc.construct(new_data + i, data[i]);
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, len);
        data = new_data;
    }
};
