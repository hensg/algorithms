#include <iostream>
#include <stack>
#include "binary_search_tree.h"

template <typename T>
void BST<T>::rebalance(Node<T>* node) {
    if (node == nullptr || node->parent == nullptr)
        return;

    Node<T>* subtree_root = node->parent;
    int left_height = 0, right_height = 0, height_diff = 0;
    while (subtree_root != nullptr) {
        left_height = 0, right_height = 0, height_diff = 0;
        if (subtree_root->left != nullptr)
            left_height = subtree_root->left->height;
        if (subtree_root->right != nullptr)
            right_height = subtree_root->right->height;

        height_diff = left_height - right_height;
        if (height_diff > 1)
            rotate_right(subtree_root);
        else if (height_diff < -1)
            rotate_left(subtree_root);

        subtree_root = subtree_root->parent;
    }
};

template <typename T>
void BST<T>::rotate_left(Node<T>* subtree_root) {
    Node<T>* tmp = subtree_root->parent;
    Node<T>* tmp_left = subtree_root->right->left;
    subtree_root->parent = subtree_root->right;
    subtree_root->right->left = subtree_root;
    subtree_root->right->parent = tmp;
    if (tmp == nullptr)
        root = subtree_root->right;
    else
        tmp->right = subtree_root->right;
       
    subtree_root->right = tmp_left;
    if (tmp_left != nullptr)
        tmp_left->parent = subtree_root;
    recalculate_sizes(subtree_root);
    recalculate_height(subtree_root);
}

template <typename T>
void BST<T>::rotate_right(Node<T>* subtree_root) {
    Node<T>* tmp = subtree_root->parent;
    Node<T>* tmp_right = subtree_root->left->right;
    subtree_root->parent = subtree_root->left;
    subtree_root->left->right = subtree_root;
    subtree_root->left->parent = tmp;
    if (tmp == nullptr)
        root = subtree_root->left;
    else
        tmp->left = subtree_root->left;
       
    subtree_root->left = tmp_right;
    if (tmp_right != nullptr)
        tmp_right->parent = subtree_root;
    recalculate_sizes(subtree_root);
    recalculate_height(subtree_root);
}

template <typename T>
void BST<T>::insert(T data) {
    Node<T>* new_node = new Node<T>();
    new_node->data = data;
    new_node->size = 1;
    new_node->height = 1;

    if (root == nullptr) {
        std::cout << "No root, creating pointer and setting data" << std::endl;
        root = new_node;
    } else {
        Node<T>* tmp = root;
        Node<T>* curr;
        while (tmp != nullptr) {
            curr = tmp;
            data < tmp->data ? tmp = tmp->left : tmp = tmp->right;
        }
        new_node->parent = curr;
        data < curr->data ? curr->left = new_node : curr->right = new_node;

        recalculate_sizes(new_node);
        recalculate_height(new_node);
        rebalance(new_node);
    }
};

template <typename T>
void BST<T>::recalculate_height(Node<T>* node) {
    Node<T>* tmp = node;
    int left_height = 0, right_height = 0;
    while (tmp != nullptr) {
        tmp->left != nullptr ? left_height = tmp->left->height : 0;
        tmp->right != nullptr ? right_height = tmp->right->height : 0;

        if (left_height > right_height)
            tmp->height = left_height + 1;
        else
            tmp->height = right_height + 1;
        tmp = tmp->parent;
    }
};

template <typename T>
void BST<T>::recalculate_sizes(Node<T>* node) {
    Node<T>* tmp = node;
    int left_size = 0, right_size = 0;
    while (tmp != nullptr) {
        tmp->left != nullptr ? left_size = tmp->left->size : 0;
        tmp->right != nullptr ? right_size = tmp->right->size : 0;
        tmp->size = left_size + right_size + 1;
        tmp = tmp->parent;
    }
};

template <typename T>
void BST<T>::print() {
    std::cout << "Printing tree" << std::endl;
    std::stack<Node<T>*> stack;

    Node<T>* curr = root, previous; 
    while (curr != nullptr || !stack.empty()) {
        while (curr != nullptr) {
            stack.push(curr);
            curr = curr->left;
        }
        curr = stack.top();
        stack.pop();
        std::cout << curr->data << "[size=" << curr->size << ",height=" << curr->height << "], ";

        curr = curr->right;
    }
    if (root != nullptr) {
        std::cout << std::endl << "Tree size=" << root->size << ",height=" << root->height << std::endl;
        std::cout << "Tree root: " << root->data << std::endl;
    }
}

template class BST<int>;