#pragma once

template <typename T>
class Deque
{
public:
    virtual bool is_empty() const = 0;
    virtual const T& front() const = 0;
    virtual T& front() = 0;
    virtual const T& back() const = 0;
    virtual T& back() = 0;
    virtual void push_front(const T& x) = 0;
    virtual void pop_front() = 0;
    virtual void push_back(const T& x) = 0;
    virtual void pop_back() = 0;
    virtual ~Deque() {}
};
