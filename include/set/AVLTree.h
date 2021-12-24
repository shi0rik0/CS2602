//
// Created by zsy on 2021/11/26.
//

#ifndef CLION_PROJ_AVLTREE_H
#define CLION_PROJ_AVLTREE_H

#include "bintree/Algorithms.h"
#include "bintree/BinaryTreeNode.h"
#include "set/AbstractSet.h"

#include <algorithm>

template <typename T>
class AVLTree : AbstractSet<T> {
public:
    int get_size() const override {
        return size;
    }
    bool contain(const T& x) const override {
        return find_node(root, x) != nullptr;
    }
    bool add(const T& x) override {
        add(x, root);
        return false; //先这么做
    }
    bool remove(const T& x) override {
        remove(x, root);
        return false; //先这么做
    }

private:
    AVLTreeNode<T>* root = nullptr;
    int size = 0;

    static void add(const T& x, AVLTreeNode<T>*& t) {
        if (t == nullptr) {
            t = new AVLTreeNode<T>();
            t->data = x;
        } else if (x < t->data) {
            add(x, t->left);
            if (get_height(t->left) - get_height(t->right) == 2) {
                if (x < t->left->data) {
                    rotate_ll(t);
                } else {
                    rotate_lr(t);
                }
            }
        } else if (x > t->data) {
            add(x, t->right);
            if (get_height(t->right) - get_height(t->left) == 2) {
                if (x > t->right->data) {
                    rotate_rr(t);
                } else {
                    rotate_rl(t);
                }
            }
        }
        update_height(t);
    }

    static bool remove(const T& x, AVLTreeNode<T>*& t) {
        if (t == nullptr) {
            return true;
        }
        if (x == t->data) {
            if (t->left == nullptr || t->right == nullptr) {
                auto old_node = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete old_node;
                return false;
            } else {
                auto tmp = t->right;
                while (tmp->left != nullptr) {
                    tmp = tmp->left;
                }
                t->data = tmp->data;
                if (remove(tmp->data, t->right)) {
                    return true;
                }
                return adjust_right(t);
            }
        }

        if (x < t->data) {
            if (remove(x, t->left)) {
                return true;
            }
            return adjust_left(t);
        } else {
            if (remove(x, t->right)) {
                return true;
            }
            return adjust_right(t);
        }
    }

    static bool adjust_left(AVLTreeNode<T>*& t) {
        if (get_height(t->right) - get_height(t->left) == 1) {
            return true;
        }
        if (get_height(t->right) == get_height(t->left)) {
            --t->height;
            return false;
        }
        if (get_height(t->right->left) > get_height(t->right->right)) {
            rotate_rl(t);
            return false;
        }
        rotate_rr(t);
        if (get_height(t->right) == get_height(t->left)) {
            return false;
        } else {
            return true;
        }
    }

    static bool adjust_right(AVLTreeNode<T>*& t) {
        if (get_height(t->left) - get_height(t->right) == 1) {
            return true;
        }
        if (get_height(t->right) == get_height(t->left)) {
            --t->height;
            return false;
        }
        if (get_height(t->left->right) > get_height(t->left->left)) {
            rotate_lr(t);
            return false;
        }
        rotate_ll(t);
        if (get_height(t->right) == get_height(t->left)) {
            return false;
        } else {
            return true;
        }
    }


    static void rotate_ll(AVLTreeNode<T>*& node) {
        AVLTreeNode<T>* node_left = node->left;
        node->left = node_left->right;
        node_left->right = node;
        update_height(node);
        update_height(node_left);
        node = node_left;
    }
    static void rotate_rr(AVLTreeNode<T>*& node) {
        AVLTreeNode<T>* node_right = node->right;
        node->right = node_right->left;
        node_right->left = node;
        update_height(node);
        update_height(node_right);
        node = node_right;
    }
    static void rotate_lr(AVLTreeNode<T>*& node) {
        rotate_rr(node->left);
        rotate_ll(node);
    }
    static void rotate_rl(AVLTreeNode<T>*& node) {
        rotate_ll(node->right);
        rotate_rr(node);
    }
    static int get_height(AVLTreeNode<T>* node) {
        return node != nullptr ? node->height : 0;
    }
    static void update_height(AVLTreeNode<T>* node) {
        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
    }

};


#endif //CLION_PROJ_AVLTREE_H
