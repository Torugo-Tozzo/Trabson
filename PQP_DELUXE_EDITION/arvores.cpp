#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <typename T>
class Node
{
public:
    T value;
    Node *left;
    Node *right;
    int height;

    Node(T value)
    {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

template <typename T>
class AVL
{
public:
    Node<T> *root;

    AVL()
    {
        root = nullptr;
    }

    int height(Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalance(Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node<T> *insert(Node<T> *node, T value)
    {
        if (node == nullptr)
            return new Node<T>(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        if (balance > 1 && value > node->left->value)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
       }

    Node<T> *deleteNode(Node<T> *node, T value)
    {
        if (node == nullptr)
            return node;

        if (value < node->value)
            node->left = deleteNode(node->left, value);

        else if (value > node->value)
            node->right = deleteNode(node->right, value);

        else
        {
            if ((node->left == nullptr) || (node->right == nullptr))
            {
                Node<T> *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                Node<T> *temp = minValueNode(node->right);

                node->value = temp->value;

                node->right = deleteNode(node->right, temp->value);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    void inOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            inOrder(node->left);
            cout << node->value << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            cout << node->value << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->value << " ";
        }
    }
};

template <typename T>
class BinaryTree
{
public:
    Node<T> *root;

    BinaryTree()
    {
        root = nullptr;
    }

    Node<T> *insert(Node<T> *node, T value)
    {        if (node == nullptr)
            return new Node<T>(value);

        if (value < node->value)
            node->left = insert(node->left, value);

        else if (value > node->value)
            node->right = insert(node->right, value);

        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    Node<T> *deleteNode(Node<T> *node, T value)
    {
        if (node == nullptr)
            return node;

        if (value < node->value)
            node->left = deleteNode(node->left, value);

        else if (value > node->value)
            node->right = deleteNode(node->right, value);

        else
        {
            if ((node->left == nullptr) || (node->right == nullptr))
            {
                Node<T> *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                Node<T> *temp = minValueNode(node->right);

                node->value = temp->value;

                node->right = deleteNode(node->right, temp->value);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    void inOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            inOrder(node->left);
            cout << node->value << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            cout << node->value << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->value << " ";
        }
    }
};


