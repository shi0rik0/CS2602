#include <iostream>

using namespace std;

template <class T>
class LinkList
{
private:
	struct node {
		T data;
		node* next;
		node(const T& x, node* p = nullptr)
		{
			data = x;
			next = p;
		}
		node() : next(nullptr) {}
		~node() {}
	};

	node* head;
	int size = 0;
public:
	LinkList();
	int length() const {
		return size;
	}
	T visit(int i) const;
	void insert(int i, const T& x);
	void remove(int i);
	void clear();
};

template <class T>
LinkList<T>::LinkList()
{
	head = new node();
}

template<class T>
inline T LinkList<T>::visit(int n) const
{
	node* p = head;
	for (int i = 0; i < n; ++i) {
		p = p->next;
	}
	return p->data;
}

template <class T>
void LinkList<T>::insert(int i, const T& x)
//注意5个原则
{
	if (i < 0) return;
	node* tmp, * p = head; //p指向头结点
	for (int j = 0; p && j < i - 1; ++j)  p = p->next;
	if (!p) return; //第i个位置不存在
	tmp = new node(x, p->next);//new+武装自己—二合一语句
	p->next = tmp; //理解头结点作用：新插入结点前永远都有一个结点
	++size;
}

template <class T>
void LinkList<T>::remove(int i)
{
	if (i < 0) return;
	node* tmp, * p = head;
	for (int j = 0; p && j < i - 1; ++j)  p = p->next;
	if (!p || !p->next) return; //第i个位置元素不存在
	tmp = p->next;
	p->next = tmp->next;
	delete tmp;
	--size;
}

template<class T>
inline void LinkList<T>::clear()
{
	node* p, * q;
	p = head->next;
	head->next = nullptr;
	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}
	size = 0;
}


int main() {
	int T;
	cin >> T;
	for (int _ = 0; _ < T; ++_) {
		LinkList<int> stack;
		int n;
		cin >> n;
		int m;
		cin >> m;
		int k = 0;
		for (int i = 1; i <= n; ++i) {
			stack.insert(0, i);
			while (stack.length() && stack.visit(1) == m) {
				stack.remove(0);
				++k;
				if (k < n) {
					cin >> m;
				}
			}
		}
		if (stack.length() == 0) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
		stack.clear();
		++k;
		while (k < n) {
			cin >> m;
			++k;
		}
	}
	return 0;
}
