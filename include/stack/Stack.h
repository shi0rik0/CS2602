#pragma once

template <typename T>
class Stack
{
public:
	virtual bool is_empty() const = 0;
	virtual T& top() = 0;
	virtual const T& top() const = 0;
	virtual void push(const T& x) = 0;
	virtual void pop() = 0;
	virtual ~Stack() {}
};
