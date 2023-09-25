#include <iostream>
#include <vector>
#include <thread>

#define NIL nullptr

template<typename T>
struct Node {
    T key;
    Node *prev = NIL;
    Node *next = NIL;
    Node(T v):key(v) {}
};

template<typename T>
struct LinkedList {
    Node<T> *head = NIL;

    Node<T>* search(T k) {
        Node<T>* x = head;
        while (x != NIL && x->key != k) {
            x = x->next;
        }
        return x;
    }

    void insert(Node<T> *x) {
        x->next = head;
        if (head != NIL) head->prev = x;
        head = x;
        x->prev = NIL;
    }

    void remove(Node<T> *x) {
        if (x->prev != NIL) {
            x->prev->next = x->next;
        } else {
            this->head = x->next;
        }
        if (x->next != NIL) {
            x->next->prev = x->prev;
        }
    }
};

int main () {
    LinkedList<int> list;
    std::cout << list.head << std::endl;
    list.insert(new Node<int>(12));
    std::cout << list.head << std::endl;
    list.insert(new Node<int>(10));
    std::cout << list.head << std::endl;
    auto find = list.search(10);
    list.remove(find);
    std::cout << list.head << std::endl;
    return 0;
}