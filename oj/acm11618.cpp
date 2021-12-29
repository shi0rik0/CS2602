#include <iostream>
#include <memory>

using namespace std;


template <class T>
class List
{
public:
    virtual int length() const = 0;
    virtual T& operator[](int i) = 0;
    virtual const T& operator[](int i) const = 0;
    virtual void insert(int i, const T& e) = 0;
    virtual void remove(int i) = 0;
    virtual void clear() = 0;
    virtual ~List() {};
};


template <class T>
class SeqList : public List<T>
{
private:
    T* data = nullptr;
    int len = 0;
    int max_len = 0;
    std::allocator<T> alloc;

    void double_space() {
        max_len *= 2;
        T* new_data = alloc.allocate(max_len);
        for (int i = 0; i < len; ++i) {
            alloc.construct(new_data + i, data[i]);
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, len);
        data = new_data;
    }
public:
    SeqList(int initSize = 64) : max_len(initSize) {
        data = alloc.allocate(initSize);
    }
    ~SeqList() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, max_len);
    }
    int length() const {
        return len;
    }
    T& operator[](int i) {
        return data[i];
    }
    const T& operator[](int i) const
    {
        auto& r = *const_cast<SeqList*>(this);
        return r[i];
    }
    template <typename U>
    void splice(int i, int dn, const U& start, const U& end) {
        int in = end - start;
        int new_len = len - dn + in;
        while (max_len < new_len) {
            double_space();
        }
        if (dn < in) {
            for (int j = len - 1; j >= len - in + dn; --j) {
                alloc.construct(data + j + in - dn, data[j]);
            }
            for (int j = len - in + dn - 1; j >= i + dn; --j) {
                data[j + in - dn] = data[j];
            }
        } else {
            for (int j = i + dn; j < len; ++j) {
                data[j + in - dn] = data[j];
            }
            for (int j = new_len; j < len; ++j) {
                alloc.destroy(data + j);
            }
        }
        for (int j = 0; j < in; ++j) {
            data[i + j] = start[j];
        }
        len = new_len;
    }
    void insert(int i, const T& e) {
        if (len == max_len) {
            double_space();
        }
        alloc.construct(data + len, data[len - 1]);
        for (int j = len - 2; j >= i; --j) {
            data[j + 1] = data[j];
        }
        data[i] = e;
        ++len;
    }
    void remove(int i) {
        for (int j = i + 1; j < len; ++j) {
            data[j - 1] = data[j];
        }
        alloc.destroy(data + len - 1);
        --len;
    }
    void clear() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        len = 0;
    }
};

template <typename T>
class DoublyLinkedList : List<T> {
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
        auto& r = *const_cast<DoublyLinkedList*>(this);
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

template <typename T>
class Deque
{
public:
    virtual bool is_empty() const = 0;
    virtual const T& front() const = 0;
    virtual T& front() = 0;
    virtual const T& back() const = 0;
    virtual T& back() = 0;
    virtual void push_front(const T& x) = 0;
    virtual void pop_front() = 0;
    virtual void push_back(const T& x) = 0;
    virtual void pop_back() = 0;
    virtual ~Deque() {}
};

template <typename T>
class LinkedDeque : public Deque<T> {
private:
    DoublyLinkedList<T>* head;
    DoublyLinkedList<T>* rear;
public:
    LinkedDeque() {
        head = new DoublyLinkedList<T>();
        rear = head;
    }
    virtual bool is_empty() const {
        return rear == head;
    }
    virtual const T& front() const {
        auto& r = *const_cast<LinkedDeque*>(this);
        return r.front();
    }
    virtual T& front() {
        return head->data;
    }
    virtual const T& back() const {
        auto& r = *const_cast<LinkedDeque*>(this);
        return r.back();
    }
    virtual T& back() {
        return rear->prev->data;
    }
    virtual void push_front(const T& x) {
        head->insert(-1, x);
        head = head->prev;
    }
    virtual void pop_front() {
        head = head->next;
        head->remove(-1);
    }
    virtual void push_back(const T& x) {
        rear->insert(1, x);
        rear = rear->next;
    }
    virtual void pop_back() {
        rear = rear->prev;
        rear->remove(1);
    }
    virtual ~LinkedDeque() {
        head->clear();
        delete head;
    }
};

int main() {
    SeqList<int> nums;
	LinkedDeque<int> max_queue;
	LinkedDeque<int> min_queue;
	int N, K;
	cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        int n;
        cin >> n;
        nums.insert(nums.length(), n);
    }
	for (int i = 0; i < K-1; ++i) {
        while (!max_queue.is_empty() && nums[max_queue.back()] <= nums[i]) {
            max_queue.pop_back();
        }
        max_queue.push_back(i);
        while (!min_queue.is_empty() && nums[min_queue.back()] >= nums[i]) {
            min_queue.pop_back();
        }
        min_queue.push_back(i);
	}
    const char* seq = "";
    for (int i = K - 1; i < N; ++i) {
        while (!min_queue.is_empty() && nums[min_queue.back()] >= nums[i]) {
            min_queue.pop_back();
        }
        min_queue.push_back(i);
        if (min_queue.front() == i - K) {
            min_queue.pop_front();
        }
        cout << seq << nums[min_queue.front()];
        seq = " ";
    }
    cout << endl;

    seq = "";
    for (int i = K - 1; i < N; ++i) {
        while (!max_queue.is_empty() && nums[max_queue.back()] <= nums[i]) {
            max_queue.pop_back();
        }
        max_queue.push_back(i);
        if (max_queue.front() == i - K) {
            max_queue.pop_front();
        }
        cout << seq << nums[max_queue.front()];
        seq = " ";
    }
    return 0;
}