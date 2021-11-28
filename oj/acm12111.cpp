#include <iostream>
#include <type_traits>

using namespace std;


template <typename T>
class BinaryTreeNode {
public:
    using ElemType = T;

    BinaryTreeNode<T>* left = nullptr;
    BinaryTreeNode<T>* right = nullptr;
    T data;
};

template <typename T>
struct DefaultCmp {
    enum {Gt, Lt, Eq};
    int operator()(const T& x1, const T& x2) {
        if (x1 < x2) {
            return Lt;
        } else if (x1 > x2) {
            return Gt;
        } else {
            return Eq;
        }
    }
};


template <typename NodePtr>
NodePtr& find_min_node(NodePtr& node) {
    auto pp = &node;
    while ((*pp)->left != nullptr) {
        pp = &((*pp)->left);
    }
    return *pp;
}

template <typename T>
using add_const_ref_t = std::add_lvalue_reference_t<std::add_const_t<T>>;

template <typename NodePtr, typename Cmp=DefaultCmp<typename std::remove_pointer_t<NodePtr>::ElemType>>
NodePtr* find_node(NodePtr& node, add_const_ref_t<typename std::remove_pointer_t<NodePtr>::ElemType> x) {
    auto pp = &node;
    while (*pp != nullptr) {
        auto result = Cmp()(x, (*pp)->data);
        if (result == Cmp::Lt) {
            pp = &((*pp)->left);
        } else if (result == Cmp::Gt) {
            pp = &((*pp)->right);
        } else {
            return pp;
        }
    }
    return nullptr;
}

int abs(int x) {
    return x >= 0 ? x : -x;
}

template <typename T, typename Cmp=DefaultCmp<T>>
class BST {
public:
    T find_min(T n) const {
        auto node = root;
        int m = abs(node->data - n);
        while (true) {
            if (node->data > n) {
                node = node->left;
            } else if (node->data < n) {
                node = node->right;
            } else {
                return 0;
            }
            if (node == nullptr) {
                break;
            }
            int m2 = abs(node->data - n);
            if (m2 < m) {
                m = m2;
            }
        }
        return m;
    }
    bool add(const T& x) {
        auto* pp = &root;
        while (*pp != nullptr) {
            auto result = Cmp()(x, (**pp).data);
            if (result == Cmp::Lt) {
                pp = &(**pp).left;
            } else if (result == Cmp::Gt) {
                pp = &(**pp).right;
            } else {
                return false;
            }
        }
        *pp = new BinaryTreeNode<T>();
        (**pp).data = x;
        return true;
    }

    bool remove(const T& x) {
        auto pp = find_node(root, x);
        if (pp != nullptr) {
            auto& p = *pp;
            if (p->left != nullptr && p->right != nullptr) {
                auto& minNode = find_min_node(p->right);
                p->data = minNode->data;
                BinaryTreeNode<T>* oldNode = minNode;
                minNode = (minNode->left != nullptr) ? minNode->left : minNode->right;
                delete oldNode;
            } else {
                BinaryTreeNode<T>* oldNode = p;
                p = (p->left != nullptr) ? p->left : p->right;
                delete oldNode;
            }
            return true;
        }
        return false;
    }

private:
    BinaryTreeNode<T>* root = nullptr;
};




int main() {
    BST<int> bst;
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int op;
        int n;
        cin >> op >> n;
        switch (op) {
            case 0:
                cout << bst.find_min(n) << endl;
                break;
            case 1:
                bst.add(n);
                break;
            case 2:
                bst.remove(n);
                break;
        }
    }
    return 0;
}