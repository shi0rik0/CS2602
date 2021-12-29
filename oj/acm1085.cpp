#include <iostream>

using namespace std;

template <typename T>
class LinkListNode {
public:
	LinkListNode(const T& d, LinkListNode* n = nullptr) : data(d), next(n) {}
	T data;
	LinkListNode* next;
	LinkListNode* insert(const T& d) {
		LinkListNode* t = next;
		next = new LinkListNode(d, t);
		return next;
	}
	void remove() {
		LinkListNode* t = next;
		next = next->next;
		delete t;
	}
};


int main() {
	int n;
	int m;
	cin >> n >> m;
	LinkListNode<int> head(0);
	auto* p = &head;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		p = p->insert(a);
	}
	for (int i = 0; i < m; ++i) {
		int opt;
		cin >> opt;
		int x, y;
		auto* p = &head;
		switch (opt) {
		case 1:
			cin >> x >> y;
			for (int j = 0; j < x; ++j) {
				p = p->next;
			}
			p->insert(y);
			break;
		case 2:
			cin >> x;
			for (int j = 0; j < x - 1; ++j) {
				p = p->next;
			}
			p->remove();
			break;
		default:
			return 1;
		}
	}
	const char* sep = "";
	for (auto* p = head.next; p; p = p->next) {
		cout << sep << p->data;
		sep = " ";
	}
	return 0;
}