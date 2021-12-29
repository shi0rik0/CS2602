#pragma once

#include <iostream>
#include <memory>

using namespace std;

template <class T>
class SeqList
{
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

public:
    SeqList(int initSize = 64) : max_len(initSize) {
        data = alloc.allocate(initSize);
    }
    ~SeqList() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, max_len);
    }
    int length() const {
        return len;
    }
    T& operator[](int i) {
        return data[i];
    }
    const T& operator[](int i) const
    {
        auto& r = *const_cast<SeqList*>(this);
        return r[i];
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
    void clear() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        len = 0;
    }
};


template <typename T>
class MinHeap {
public:
    MinHeap(int init_size = 64) : data(init_size + 1) {
        data.insert(0, T());
    }
    bool is_empty() const {
        return length() == 0;
    }
    void enqueue(const T& x) {
        int i;
        data.insert(data.length(), T());
        for (i = length(); i > 1 && x < data[i / 2]; i /= 2) {
            data[i] = data[i / 2];
        }
        data[i] = x;
    }
    void dequeue() {
        data[1] = data[length()];
        percolateDown(1);
        data.remove(data.length() - 1);
    }
    const T& front() {
        return data[1];
    }
    int length() const {
        return data.length() - 1;
    }
private:
    SeqList<T> data;

    void percolateDown(int hole) {
        int child;
        T tmp = data[hole];

        for (; hole * 2 <= length(); hole = child) {
            child = hole * 2;
            if (child != length() && data[child + 1] < data[child]) {
                ++child;
            }
            if (data[child] < tmp) {
                data[hole] = data[child];
            } else {
                break;
            }
        }
        data[hole] = tmp;
    }
};

int gcd(int m, int n) {
    if (m < n) {
        int t = m;
        m = n;
        n = t;
    }
    while (n) {
        int t = m % n;
        m = n;
        n = t;
    }
    return m;
}

class Fraction {
public:
    int a;
    int b;
    Fraction(int a_ = 0, int b_ = 0) : a(a_), b(b_) {}
    bool operator<(const Fraction& rhs) const {
        long long m = (long long)a * rhs.b;
        long long n = (long long)rhs.a * b;
        return m > n;
    }
};

int main() {
    int N, K;
    cin >> N >> K;
    MinHeap<Fraction> h(K);
    for (int i = 2; i <= N; ++i) {
        h.enqueue(Fraction(i - 1, i));
    }
    Fraction cur;
    while (K--) {
        cur = h.front();
        h.dequeue();
        int a = cur.a - 1;
        int b = cur.b;
        while (a && gcd(a, b) != 1) {
            --a;
        }
        if (a) {
            h.enqueue(Fraction(a, b));
        }
    }
    cout << cur.a << '/' << cur.b;
    return 0;
}