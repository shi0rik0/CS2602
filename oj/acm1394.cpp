#include <iostream>

using namespace std;


template <class elemType>
class list
{
public:
    virtual int length() const = 0;
    virtual int search(const elemType& x) const = 0;
    virtual elemType visit(int i) const = 0;
    virtual void insert(int i, const elemType& x) = 0;
    virtual void remove(int i) = 0;
    virtual void clear() = 0;
    virtual void traverse() const = 0;
    virtual ~list() {};  //注意观察：有析构函数，没有构造函数
};

class OutOfBound {};
class IllegalSize {};

template <class elemType>
class seqList : public list<elemType>
{
private:
    elemType* data;
    int currentLength;
    int maxSize;
    void doubleSpace();
public:
    seqList(int initSize = 10); //构造函数
    ~seqList() { delete[] data; }
    int length() const;
    int search(const elemType& x) const; //存在返回下标，不存在返回-
    elemType visit(int i) const;
    void insert(int i, const elemType& x);
    void remove(int i);
    void clear();
    void traverse() const;
};


template <class elemType>
seqList< elemType >::seqList(int initSize) //注意帽子和胡子！
{
    data = new elemType[initSize];
    if (!data) throw IllegalSize();
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
int seqList< elemType >::length() const
{
    return currentLength;
}

template <class elemType>
int seqList< elemType >::search(const elemType& x) const
{
    int i = 0;
    for (; i < currentLength; i++)
        if (data[i] == x) break;
    if (i == currentLength) return -1;
    else return i;
}
//实现visit
template <class elemType>
elemType seqList< elemType >::visit(int i) const
{
    return data[i];
}

template <class elemType>
void seqList< elemType >::insert(int i, const elemType& x)
{
    if (i > currentLength || i < 0) return;
    if (currentLength == maxSize)
        doubleSpace();
    for (int j = currentLength; j > i; j--)
        data[j] = data[j - 1]; //注意两个边界的检查
    data[i] = x;
    currentLength++;
}

template <class elemType>
void seqList< elemType >::doubleSpace()
{
    elemType* tmp = new elemType[maxSize * 2];
    if (!tmp) throw IllegalSize();
    for (int j = 0; j < length(); ++j)  tmp[j] = data[j];
    delete[]data;
    data = tmp;
    maxSize = maxSize * 2;
}

template <class elemType>
void seqList< elemType >::remove(int i)
{
    if (i > currentLength || i < 0) return;
    for (int j = i; j < currentLength - 1; j++)
        data[j] = data[j + 1]; //注意两个边界的检查
    currentLength--;
}

template <class elemType>
void seqList< elemType >::clear()
{
    currentLength = 0;
}

template <class elemType>
void seqList< elemType >::traverse() const
{
    for (int j = 0; j < currentLength; j++)
        cout << data[j];
}


int main() {
    seqList<int> a1;
    int n;
    cin >> n;
    for (int _ = 0; _ < n; ++_) {
        int k;
        cin >> k;
        a1.insert(a1.length(), k);
    }
    seqList<int> a2;
    int m;
    cin >> m;
    for (int _ = 0; _ < m; ++_) {
        int k;
        cin >> k;
        a2.insert(a2.length(), k);
    }
    int i = 0;
    int j = 0;
    const char* sep = "";
    for (int _ = 0; _ < m + n; ++_) {
        int n1 = 99999999;
        int n2 = 99999999;
        if (i < n) {
            n1 = a1.visit(i);
        }
        if (j < m) {
            n2 = a2.visit(j);
        }
        if (n1 < n2) {
            cout << sep << n1;
            ++i;
        } else {
            cout << sep << n2;
            ++j;
        }
        sep = " ";
    }
	return 0;
}