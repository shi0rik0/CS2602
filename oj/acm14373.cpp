#include <iostream>

using namespace std;

template <class elemType>
class seqQueue
{
private:
    elemType* elem;
    int maxSize;
    int front, rear;
    void doubleSpace();
public:
    seqQueue(int size = 64)
    {
        elem = new elemType[size];
        maxSize = size; front = rear = 0;
    }
    ~seqQueue() { delete[] elem; }
    bool isEmpty() const { return front == rear; }
    elemType getFront() const
    {
        return front % maxSize;
    }
    elemType getRear() const
    {
        return rear % maxSize;
    }
    int getLength() const {
        return (rear - front) % maxSize;
    }
    void enQueue(const elemType& x);
    elemType deQueue();
};

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType* tmp = elem;
    elem = new elemType[2 * maxSize];
    for (int i = 1; i < maxSize; ++i)
        elem[i] = tmp[(front + i) % maxSize];

    front = 0; rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType& x)
{
    if ((rear + 1) % maxSize == front) doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

int main() {
    int s, n;
    cin >> s >> n;
    seqQueue<int> queue(s);
    for (int i = 0; i < n; ++i) {
        int op;
        cin >> op;
        if (op == 0) {
            int x;
            cin >> x;
            queue.enQueue(x);
            cout << queue.getRear() << ' ' << queue.getLength() << endl;
        } else {
            if (!queue.isEmpty()) {
                queue.deQueue();
            }
            cout << queue.getFront() << ' ' << queue.getLength() << endl;
        }
    }
    return 0;
}