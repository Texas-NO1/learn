#include <iostream>
#include <vector>
#include <thread>

template<typename T>
struct Node {
    T key;
    Node *prev;
    Node *next;
    Node(T v):key(v) {}
};

template<typename T>
struct LinkedList {
    Node<T> *nil;
    LinkedList() {
        nil = new Node<T>(T());
        nil->prev = nil;
        nil->next = nil;
    }


    Node<T>* search(T k) {
        Node<T>* x = nil->next;
        while (x != nil && x->key != k) {
            x = x->next;
        }
        return x;
    }

    void insert(Node<T> *x) {
        x->next = nil->next;
        nil->next->prev = x;
        nil->next = x;
        x->prev = nil;
    }

    void remove(Node<T> *x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
};

int main () {
    LinkedList<int> list;
    std::cout << list.nil << " " << list.nil->next << std::endl;
    list.insert(new Node<int>(12));
    std::cout << list.nil << " " << list.nil->next << std::endl;
    list.insert(new Node<int>(10));
    std::cout << list.nil << " " << list.nil->next << std::endl;
    auto find = list.search(10);
    list.remove(find);
    std::cout << list.nil << " " << list.nil->next << std::endl;
    return 0;
}