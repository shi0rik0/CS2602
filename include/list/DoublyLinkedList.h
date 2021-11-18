#pragma once


template <typename T>
class DoublyLinkedList {
public:
	T data;
	DoublyLinkedList* next = nullptr;
	DoublyLinkedList* prev = nullptr;
	void insert(int i, const T& d) {
		if (i > 0) {
			--i;
			auto* node1 = get_node(i);
			auto* node2 = node1->next;
			node1->next = new DoublyLinkedList();
			node1->data = d;
			node1->next->next = node2;
			node1->next->prev = node1;
			if (node2) {
				node2->prev = node1->next;
			}
		} else {
			++i;
			auto* node1 = get_node(i);
			auto* node2 = node1->prev;
			node1->prev = new DoublyLinkedList();
			node1->data = d;
			node1->prev->prev = node2;
			node1->prev->next = node1;
			if (node2) {
				node2->next = node1->prev;
			}
		}
	}
	void remove(int i) {
		auto* node = get_node(i);
		if (node->next) {
			node->next->prev = node->prev;
		}
		if (node->prev) {
			node->prev->next = node->next;
		}
		delete node;
	}
	int length() const {
		int n = 1;
		for (auto* p = next; p; p = p->next) {
			++n;
		}
		for (auto* p = prev; p; p = p->prev) {
			++n;
		}
		return n;
	}
	T& operator[](int i) {
		return get_node(i)->data;
	}
	const T& operator[](int i) const {
		auto& r = *const_cast<DoublyLinkedList*>(this);
		return r[i];
	}
	DoublyLinkedList* get_node(int i) {
		auto* p = this;
		if (i >= 0) {
			for (int _ = 0; _ < i; ++_) {
				p = p->next;
			}
		} else {
			for (int _ = 0; _ > i; --_) {
				p = p->prev;
			}
		}
		return p;
	}
	const DoublyLinkedList* get_node(int i) const {
		auto& r = *const_cast<LinkedList*>(this);
		return r.get_node(i);
	}
	void clear() {
		DoublyLinkedList* q = nullptr;
		for (auto* p = next; p; p = q) {
			q = p->next;
			delete p;
		}
		for (auto* p = prev; p; p = q) {
			q = p->prev;
			delete p;
		}
	}
};
