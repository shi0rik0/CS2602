#pragma once

#include "Stack.h"
#include "list/SeqList.h"

template <class T>
class SeqStack : public Stack<T>
{
private:
	SeqList<T> list;
public:
	SeqStack(int initSize = 64) : list(initSize) {}

	bool is_empty() const {
		return list.length() == 0;
	}
	T& top() {
		return list[list.length() - 1];
	}
	const T& top() const {
		return list[list.length() - 1];
	}
	void pop() {
		list.remove(list.length() - 1);
	}
	void push(const T& x) {
		list.insert(list.length(), x);
	}
	int size() const {
		return list.length();
	}
};
