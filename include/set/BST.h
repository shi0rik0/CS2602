#ifndef CLION_PROJ_BST_H
#define CLION_PROJ_BST_H

#include "set/AbstractSet.h"
#include "bintree/BinaryTreeNode.h"
#include "bintree/Algorithms.h"
#include "utils/Comparator.h"
#include "Exceptions.h"


template <typename T, typename Cmp=DefaultCmp<T>>
class BST : AbstractSet<T> {
public:
    int get_size() const override {
        return size;
    }
//    bool contain(const T& x) const override {
//        auto p = root;
//        while (p != nullptr) {
//            auto result = Cmp()(x, p->data);
//            if (result == Cmp::Lt) {
//                p = p->left;
//            } else if (result == Cmp::Gt) {
//                p = p->right;
//            } else {
//                return true;
//            }
//        }
//        return false;
//    }
    bool contain(const T& x) const override {
        return find_node(root, x) != nullptr;
    }

    bool add(const T& x) override {
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

    // 需要改成双重指针
//    bool remove(const T& x) override {
//        throw UnimplementedError();
//        auto& pref = root;
//        while (pref != nullptr) {
//            auto result = Cmp()(x, pref->data);
//            if (result == Cmp::Lt) {
//                pref = pref->left;
//            } else if (result == Cmp::Gt) {
//                pref = pref->right;
//            } else {
//                if (pref->left != nullptr && pref->right != nullptr) {
//                    auto& minNode = find_min_node(pref->right);
//                    pref->data = minNode->data;
//                    BinaryTreeNode<T>* oldNode = minNode;
//                    minNode = (minNode->left != nullptr) ? minNode->left : minNode->right;
//                    delete oldNode;
//                } else {
//                    BinaryTreeNode<T>* oldNode = pref;
//                    pref = (pref->left != nullptr) ? pref->left : pref->right;
//                    delete oldNode;
//                }
//            }
//        }
//        return false;
//    }

    bool remove(const T& x) override {
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
    int size = 0;
};


#endif //CLION_PROJ_BST_H
