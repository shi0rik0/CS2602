#pragma once

#include "Deque.h"
#include "list/SeqList.h"

//template <typename T>
//class SeqDeque : public Deque<T> {
//private:
//    int len = 0;
//    SeqList<T> data{ 64 };
//	int head = 0;
//	int rear = -1;
//public:
//    virtual bool is_empty() const {
//        return len == 0;
//    }
//    virtual const T& front() const {
//        auto& r = *const_cast<SeqDeque*>(this);
//        return r.front();
//    }
//    virtual T& front() {
//        return data[head];
//    }
//    virtual const T& back() const {
//        auto& r = *const_cast<SeqDeque*>(this);
//        return r.back();
//    }
//    virtual T& back() {
//        return data[rear];
//    }
//    virtual void push_front(const T& x) {
//        if (len == data.length()) {
//            data.double_space();
//        }
//        head = (head - 1) % data.length();
//        data[]
//    }
//    virtual void pop_front() = 0;
//    virtual void push_back(const T& x) = 0;
//    virtual void pop_back() = 0;
//    virtual ~Deque() {}
//};