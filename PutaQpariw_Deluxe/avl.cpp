#include <iostream>
#include <string>

using namespace std;

template <typename N>
class Node {
public:
    N data;
    int height;
    Node *left, *right;

    Node(N data) {
        this->data = data;
        height = 1;
        left = right = nullptr;
    }
};

template <typename N>
class AVL {
public:
    Node<N> *root;

    AVL() { root = nullptr; }

    int height(Node<N> *node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node<N> *node) {
        if (!node) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
template <typename N>
Node<N> *BST<N>::rightRotate(Node<N> *node) {
    Node<N> *x = node->left;
    Node<N> *T2 = x->right;

    x->right = node;
    node->left = T2;

    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

template <typename N>
Node<N> *BST<N>::leftRotate(Node<N> *node) {
    Node<N> *x = node->right;
    Node<N> *T2 = x->left;

    x->left = node;
    node->right = T2;

    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

template <typename N>
int BST<N>::getBalance(Node<N> *node) {
    if (!node) {
        return 0;
    }

    return height(node->left) - height(node->right);
}

template <typename N>
Node<N> *BST<N>::insert(Node<N> *node, N data) {
    if (!node) {
        return new Node<N>(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
};
