#pragma once

template <typename T>
class LinkedList {
public:
	LinkedList() : next(nullptr) {}
	LinkedList(LinkedList* n) : next(n) {}
	LinkedList(LinkedList* n, const T& d) : next(n), data(d) {}
	T data;
	LinkedList* next = nullptr;
	void insert(int i, const T& d) {
		LinkedList* node = get_node(i);
		LinkedList* t = node->next;
		node->next = new LinkedList(t, d);
	}
	void remove(int i) {
		LinkedList* node = get_node(i);
		LinkedList* t = node->next;
		node->next = node->next->next;
		delete t;
	}
	int length() const {
		int n = 0;
		for (auto* p = next; p; p = p->next) {
			++n;
		}
		return n;
	}
	T& operator[](int i) {
		return get_node(i + 1)->data;
	}
	const T& operator[](int i) const {
		auto& r = *const_cast<LinkedList*>(this);
		return r[i];
	}
	LinkedList* get_node(int i) {
		auto* p = this;
		for (int _ = 0; _ < i; ++_) {
			p = p->next;
		}
		return p;
	}
	const LinkedList* get_node(int i) const {
		auto& r = *const_cast<LinkedList*>(this);
		return r.get_node(i);
	}
	operator bool() const {
		return next != nullptr;
	}
	void clear() {
		LinkedList* q = nullptr;
		for (auto* p = next; p; p = q) {
			q = p->next;
			delete p;
		}
	}
};
