#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class SeqList
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
    virtual ~SeqList() {
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
    int find(const T& e) {
        int i;
        for (i = 0; i < len; ++i) {
            if (data[i] == e) {
                return i;
            }
        }
        return i;
    }
};



template <typename T>
struct BinaryTreeNode {
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    T data;
};


SeqList<int> a1; // Ç°Ðò
SeqList<int> a2; // ÖÐÐò

BinaryTreeNode<int>* create_node(int start, int end, int pre) {
    if (start == end) {
        return nullptr;
    }
    int i;
    for (i = start; i < end; ++i) {
        if (a2[i] == a1[pre]) {
            break;
        }
    }
    BinaryTreeNode<int>* node = new BinaryTreeNode<int>();
    node->data = a1[pre];
    node->left = create_node(start, i, pre + 1);
    node->right = create_node(i + 1, end, pre - start + i + 1);
    return node;
}

void post_order(BinaryTreeNode<int>* node) {
    if (!node) {
        return;
    }
    post_order(node->left);
    post_order(node->right);
    cout << node->data << " ";
}


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        a1.insert(a1.length(), m);
    }
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        a2.insert(a2.length(), m);
    }
    BinaryTreeNode<int> root;
    root.data = a1[0];
    int i = a2.find(root.data);
    root.left = create_node(0, i, 1);
    root.right = create_node(i + 1, a2.length(), i + 1);
    post_order(&root);
	return 0;
}
