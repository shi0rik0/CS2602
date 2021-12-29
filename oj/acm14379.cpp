#include <iostream>

using namespace std;

class outOfBound {};
class illegalSize {};
template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const = 0;
    virtual elemType  top() const = 0;
    virtual void push(const elemType& x) = 0;
    virtual elemType  pop() = 0;
    virtual ~stack() {}
};

template <class elemType>
class seqStack : public stack<elemType>
{
private:
    elemType* elem;
    int Top;
    int maxSize;

    void doubleSpace();
public:
    seqStack(int initSize = 10);
    ~seqStack();

    bool isEmpty() const;
    elemType top() const;
    elemType pop();
    void push(const elemType& x);
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];
    if (!elem)
    {
        throw illegalSize();
    }
    maxSize = initSize;
    Top = -1;
}

template <class elemType>
seqStack<elemType>::~seqStack()
{
    delete[] elem;
}

template <class elemType>
bool seqStack<elemType>::isEmpty() const
{
    return (Top == -1);
}

template <class elemType>
elemType seqStack<elemType>::pop()
{
    if (Top == -1) throw outOfBound(); return elem[Top--];
}

template <class elemType>
void seqStack<elemType>::push(const elemType& x)
{
    if (Top == maxSize - 1)   doubleSpace();
    elem[++Top] = x;
}


template <class elemType>
elemType seqStack<elemType>::top() const
{
    if (Top == -1) throw outOfBound(); return elem[Top];
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType* tmp = elem;
    elem = new elemType[2 * maxSize];
    for (int i = 0; i < maxSize; ++i)
        elem[i] = tmp[i];
    maxSize *= 2;
    delete[] tmp;
}

int main() {
    seqStack<char> stack;
    char c;
    cin.get(c);
    while (cin) {
        switch (c) {
        case '(':
        case '[':
        case '{':
            stack.push(c);
            break;
        case ')':
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            } else {
                cout << 0;
                return 0;
            }
            break;
        case ']':
            if (!stack.isEmpty() && stack.top() == '[') {
                stack.pop();
            } else {
                cout << 0;
                return 0;
            }
            break;
        case '}':
            if (!stack.isEmpty() && stack.top() == '{') {
                stack.pop();
            } else {
                cout << 0;
                return 0;
            }
            break;
        }
        cin.get(c);
    }
    if (!stack.isEmpty()) {
        cout << 0;
    } else {
        cout << 1;
    }
	return 0;
}