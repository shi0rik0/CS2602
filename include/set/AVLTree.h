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

    }
    bool remove(const T& x) override {

    }

private:
    AVLTreeNode* root;
    int size = 0;

    static void rotate_ll(AVLTreeNode<T>*& node) {
        AVLTreeNode<T> node_left = node->left;
        node->left = node_left->right;
        node_left->right = node;
        update_height(node);
        update_height(node_left);
        node = node_left;
    }
    static void rotate_rr(AVLTreeNode<T>*& node) {
        AVLTreeNode<T> node_right = node->right;
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
    static void update_height(AVLTreeNode<T>* node) {
        node->height = std::max(node->left->height, node->right->height) + 1;
    }
};


#endif //CLION_PROJ_AVLTREE_H
