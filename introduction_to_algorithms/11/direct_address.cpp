#include <iostream>
#include <vector>

struct Node {
    int key;
    int value;
};

Node* direct_address_search(std::vector<Node*> &T, int k) {
    return T[k];
}

void direct_address_insert(std::vector<Node*> &T, Node* x)  {
    T[x->key] = x;
}

void direct_address_delete(std::vector<Node*> &T, Node* x) {
    T[x->key] = nullptr;
}

int main () {

    return 0;
}