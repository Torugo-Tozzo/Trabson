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