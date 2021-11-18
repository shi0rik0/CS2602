#pragma once

#include <iostream>

template <typename T>
class BinaryTree;

template <typename T>
class BinaryTreePointer {
	template <typename T>
	friend BinaryTreePointer<T> make_binary_tree();
	template <typename T>
	friend BinaryTreePointer<T> make_binary_tree(const T& d);
private:
	BinaryTree<T>* p = nullptr;
	BinaryTreePointer(BinaryTree<T>* p_) : p(p_) {}
public:
	BinaryTreePointer() = default;
	BinaryTreePointer(const BinaryTreePointer& b) : p(b.p) {
		++p->ref_count;
	}
	BinaryTree<T>& operator*() {
		return *p;
	}
	const BinaryTree<T>& operator*() const {
		return *p;
	}
	BinaryTree<T>* operator->() {
		return p;
	}
	const BinaryTree<T>* operator->() const {
		return p;
	}
	BinaryTreePointer& operator=(const BinaryTreePointer& rhs) {
		if (this == &rhs) {
			return *this;
		}
		if (p) {
			--p->ref_count;
			if (p->ref_count == 0) {
				delete p;
			}
		}
		p = rhs.p;
		if (p) {
			++p->ref_count;
		}
		return *this;
	}
	~BinaryTreePointer() {
		if (p) {
			--p->ref_count;
			if (p->ref_count == 0) {
				delete p;
			}
		}
	}
	void release() {
		if (p) {
			--p->ref_count;
			if (p->ref_count == 0) {
				delete p;
			}
			p = nullptr;
		}
	}
	bool is_null() const {
		return p == nullptr;
	}
	operator bool() const {
		return p != nullptr;
	}
};

template <typename T>
class BinaryTree {
	friend class BinaryTreePointer<T>;
	template <typename T>
	friend BinaryTreePointer<T> make_binary_tree();
	template <typename T>
	friend BinaryTreePointer<T> make_binary_tree(const T& d);
private:
	int ref_count = 1;

	BinaryTree() = default;
	BinaryTree(const T & d) : data(d) {
	}
	~BinaryTree() {
	}
public:
	BinaryTreePointer<T> left;
	BinaryTreePointer<T> right;
	T data;
};

template <typename T>
BinaryTreePointer<T> make_binary_tree() {
	return BinaryTreePointer<T>(new BinaryTree<T>());
}

template <typename T>
BinaryTreePointer<T> make_binary_tree(const T& d) {
	return BinaryTreePointer<T>(new BinaryTree<T>(d));
}