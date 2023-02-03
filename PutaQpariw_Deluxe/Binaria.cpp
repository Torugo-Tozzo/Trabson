#include "arvores.h"

using namespace std;

template <typename N>
class BST {
public:
    Node<N> *root;

    BST() { root = nullptr; }

    void insert(N data) {
        root = insert(root, data);
    }

    Node<N> *insert(Node<N> *node, N data) {
        if (!node) {
            return new Node<N>(data);
        }

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }

        return node;
    }

    bool search(N data) {
        return search(root, data);
    }

    bool search(Node<N> *node, N data) {
        if (!node) {
            return false;
        }

        if (node->data == data) {
            return true;
        }

        if (data < node->data) {
            return search(node->left, data);
        } else {
            return search(node->right, data);
        }
    }

    void preOrder() {
        preOrder(root);
    }

    void preOrder(Node<N> *node) {
        if (!node) {
            return;
        }

        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder() {
        postOrder(root);
    }

    void postOrder(Node<N> *node) {
        if (!node) {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    void inOrder() {
        inOrder(root);
    }

    void inOrder(Node<N> *node) {
        if (!node) {
            return;
        }

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void printTree(Node<N> *node, int level) {
    if (!node) {
        return;
    }
    printTree(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << node->data << endl;
    printTree(node->left, level + 1);
}

};