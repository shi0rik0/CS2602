#pragma once

#include <memory>

template <typename T>
class SeqQueue {
private:
    int size;
    std::allocator<T> alloc;
    T* data;
    int head = 0;
    int rear = 0;

    void double_space() {
        T* new_data = alloc.allocate(size * 2); {
            for (int i = 0; i < rear; ++i) {
                alloc.construct(new_data + i, data[i]);
                alloc.destroy(data + i);
            }
            for (int i = head; i < size; ++i) {
                alloc.construct(new_data + size + i, data[i]);
                alloc.destroy(data + i);
            }
            alloc.deallocate(data, size);
            head += size;
            size *= 2;
            data = new_data;
        }
    }
public:
    SeqQueue(int init_size = 64) : size(init_size) {
        data = alloc.allocate(init_size);
    }
    virtual bool is_empty() const {
        return head == rear;
    }
    virtual const T& front() const {
        auto& r = *const_cast<SeqQueue*>(this);
        return r.front();
    }
    virtual T& front() {
        return data[head];
    }
    virtual void enqueue(const T& x) {
        alloc.construct(data + rear, x);
        rear = (rear + 1) % size;
        if (rear == head) {
            double_space();
        }
    }
    virtual void dequeue() {
        alloc.destroy(data + head);
        head = (head + 1) % size;
    }
    virtual ~SeqQueue() {
        for (int i = head; i != rear; ++i) {
            if (i == size) {
                i = 0;
            }
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, size);
    }
};
