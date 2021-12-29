#include <iostream>

using namespace std;


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


int main() {
	int m, n;
	cin >> m >> n;
	LinkedList<int> n1, n2;
	for (int _ = 0; _ < m; ++_) {
		int k;
		cin >> k;
		n1.insert(0, k);
	}
	for (int _ = 0; _ < n; ++_) {
		int k;
		cin >> k;
		n2.insert(0, k);
	}
	LinkedList<int> n3;
	auto* p1 = n1.get_node(1);
	auto* p2 = n2.get_node(1);
	int carry = 0;
	while (p1 || p2) {
		int d1 = 0;
		int d2 = 0;
		if (p1) {
			d1 = p1->data;
			p1 = p1->next;
		}
		if (p2) {
			d2 = p2->data;
			p2 = p2->next;
		}
		int sum = d1 + d2 + carry;
		int ans = sum % 10;
		carry = sum / 10;
		n3.insert(0, ans);
	}
	if (carry) {
		n3.insert(0, carry);
	}
	const char* sep = "";
	for (auto* p = n3.get_node(1); p; p = p->next) {
		cout << sep << p->data;
		sep = " ";
	}
	return 0;
}