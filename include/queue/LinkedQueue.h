#pragma once

#include "list/LinkedList.h"

template <typename T>
class LinkedQueue
{
private:
	LinkedList<T> head;
	LinkedList<T>* rear;
	LinkedList<T>* rear_prev = nullptr;
public:
	LinkedQueue() {
		rear = &head;
	}
	bool is_empty() const {
		return rear == &head;
	}
	T& front() {
		return head[0];
	}
	const T& front() const {
		auto& r = *const_cast<LinkedQueue*>(this);
		return r.front();
	}
	void enqueue(const T& x) {
		rear_prev = rear;
		rear->insert(0, x);
		rear = rear->next;
	}
	void dequeue() {
		if (head.next == rear) {
			rear = &head;
		}
		head.remove(0);
	}
	~LinkedQueue() {
		head.clear();
	}
	
};