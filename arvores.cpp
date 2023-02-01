#include <iostream>
#include <string>

using namespace std;

template <typename N>
class Node {
public:
    N data;
    Node *left, *right;

    Node(N data) {
        this->data = data;
        left = right = nullptr;
    }
};

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
};

int main() {
    BST<int> bstInt;

    bstInt.insert(10);
    bstInt.insert(5);
    bstInt.insert(15);
    bstInt.insert(3);
    bstInt.insert(7);

    cout << "Pre-order (int): ";
    bstInt.preOrder();
    cout << endl;

    BST<string> bstString;

    bstString.insert("dog");
    bstString.insert("alpha");
    bstString.insert("zumzi");
    bstString.insert("dragon");
    bstString.insert("dromedario");
    bstString.insert("puta ao q o pariu ao qadrado");

    bstString.preOrder();
}