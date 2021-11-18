#ifndef CLION_PROJ_BINARYTREE_H
#define CLION_PROJ_BINARYTREE_H

#include "Exceptions.h"
#include "queue/SeqQueue.h"

#include <iostream>
#include <functional>

template <typename T>
class BinaryTreeNode {
public:
    using ElemType = T;

    BinaryTreeNode<T>* get_left() const {
        return left;
    }
    void set_left(BinaryTreeNode<T>* p) {
        left = p;
    }
    BinaryTreeNode<T>* get_right() const {
        return right;
    }
    void set_right(BinaryTreeNode<T>* p) {
        right = p;
    }
    T& data_ref() {
        return data;
    }
    const T& data_ref() const {
        return data;
    }

private:
    BinaryTreeNode<T>* left = nullptr;
    BinaryTreeNode<T>* right = nullptr;
    T data;
};

template <typename T>
class BinaryTree {
public:
    using ElemType = typename T::ElemType;
    void clear() {
        root = nullptr;
    }
    bool is_empty() const {
        return root == nullptr;
    }
    T* get_root() const {
        return root;
    }
    void set_root(T* p) {
        root = p;
    }
    void del_left() const {
        del(root->get_left());
    }
    void del_right() const {
        del(root->get_right());
    }
    void del_all() const {
        del_left();
        del_right();
    }
    void pre_order(const std::function<void(ElemType&)>& func) const {
        pre_order(root, func);
    }
    void in_order(const std::function<void(ElemType&)>& func) const {
        in_order(root, func);
    }
    void post_order(const std::function<void(ElemType&)>& func) const {
        post_order(root, func);
    }
    void level_order(const std::function<void(ElemType&)>& func) const {
        SeqQueue<T*> queue;
        queue.enqueue(root);
        while (!queue.is_empty()) {
            auto p = queue.front();
            queue.dequeue();
            func(p->data_ref());
            if (p->get_left() != nullptr) {
                queue.enqueue(p->get_left());
            }
            if (p->get_right() != nullptr) {
                queue.enqueue(p->get_right());
            }
        }
    }
private:
    T* root = nullptr;

    void del(T* node) const {
        if (node == nullptr) {
            return;
        }
        del(node->get_left());
        del(node->get_right());
        delete node;
    }
    void pre_order(T* node, const std::function<void(ElemType&)>& func) const {
        if (node == nullptr) {
            return;
        }
        func(node->data_ref());
        pre_order(node->get_left(), func);
        pre_order(node->get_right(), func);
    }
    void in_order(T* node, const std::function<void(ElemType&)>& func) {
        if (node == nullptr) {
            return;
        }
        pre_order(node->get_left(), func);
        func(node->data_ref());
        pre_order(node->get_right(), func);
    }
    void post_order(T* node, const std::function<void(ElemType&)>& func) {
        if (node == nullptr) {
            return;
        }
        pre_order(node->get_left(), func);
        pre_order(node->get_right(), func);
        func(node->data_ref());
    }
};

template <typename T>
BinaryTreeNode<T>* create_tree(const T& null_flag) {
    using namespace std;
    SeqQueue<BinaryTreeNode<T>*> queue;
    cout << "输入根节点：";
    T x;
    cin >> x;
    auto root = new BinaryTreeNode<T>();
    root->data_ref() = x;
    queue.enqueue(root);

    while (!queue.is_empty()) {
        auto tmp = queue.front();
        queue.dequeue();
        cout << "输入" << tmp->data_ref() << "的两个儿子（" << null_flag << "表示空节点）：";
        T x1, x2;
        cin >> x1 >> x2;
        if (x1 != null_flag) {
            auto left = new BinaryTreeNode<T>();
            left->data_ref() = x1;
            tmp->set_left(left);
            queue.enqueue(left);
        }
        if (x2 != null_flag) {
            auto right = new BinaryTreeNode<T>();
            right->data_ref() = x2;
            tmp->set_right(right);
            queue.enqueue(right);
        }
    }
    return root;
}

#endif //CLION_PROJ_BINARYTREE_H
