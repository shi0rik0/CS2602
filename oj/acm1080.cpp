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


int main() {
	LinkList<int> stack;
	int opNum = 0;
	while (true) {
		char c;
		cin.get(c);
		if (c >= '0' && c <= '9') {
			opNum = opNum * 10 + c - '0';
		} else if (c == '.') {
			stack.insert(0, opNum);
			opNum = 0;
		} else if (c == '@') {
			cout << stack.visit(1);
			break;
		} else {
			int op2 = stack.visit(1);
			stack.remove(0);
			int op1 = stack.visit(1);
			stack.remove(0);
			switch (c)
			{
			case '+':
				stack.insert(0, op1 + op2);
				break;
			case '-':
				stack.insert(0, op1 - op2);
				break;
			case '*':
				stack.insert(0, op1 * op2);
				break;
			case '/':
				stack.insert(0, op1 / op2);
				break;
			}
		}
	}
	return 0;
}
