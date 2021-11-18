#pragma once

#include "deque/Deque.h"
#include "list/DoublyLinkedList.h"

template <typename T>
class LinkedDeque : public Deque<T> {
private:
    DoublyLinkedList<T>* head;
    DoublyLinkedList<T>* rear;
public:
    LinkedDeque() {
        head = new DoublyLinkedList<T>();
        rear = head;
    }
    virtual bool is_empty() const {
        return rear == head;
    }
    virtual const T& front() const {
        auto& r = *const_cast<LinkedDeque*>(this);
        return r.front();
    }
    virtual T& front() {
        return head->data;
    }
    virtual const T& back() const {
        auto& r = *const_cast<LinkedDeque*>(this);
        return r.back();
    }
    virtual T& back() {
        return rear->prev->data;
    }
    virtual void push_front(const T& x) {
        head->insert(-1, x);
        head = head->prev;
    }
    virtual void pop_front() {
        head = head->next;
        head->remove(-1);
    }
    virtual void push_back(const T& x) {
        rear->insert(1, x);
        rear = rear->next;
    }
    virtual void pop_back() {
        rear = rear->prev;
        rear->remove(1);
    }
    virtual ~LinkedDeque() {
        head->clear();
        delete head;
    }
};