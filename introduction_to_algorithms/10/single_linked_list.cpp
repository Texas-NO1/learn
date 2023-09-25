#include <iostream>
#include <vector>

#define NIL nullptr

struct Node {
    int key;
    Node *next = NIL;
    Node(int k) : key(k) {}
};

struct LinkedList {
    Node *head = NIL;
    Node* search(int k) {
        Node *x = head;
        while (x != NIL && x->key != k) {
            x = x->next;
        }
        return x;
    }
    void insert(Node *x) {
        x->next = head;
        head = x;
    }
    void remove(Node *x) {
        if (x == head) {
            head = x->next;
            return;
        }
        Node *tmp = head;
        while (tmp != NIL && tmp->next != x) {
            tmp = tmp->next;
        }
        if (tmp != NIL) tmp->next = x->next;
    }
    void output() {
        Node *tmp = head;
        while (tmp != NIL) {
            std::cout << tmp->key << ",";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }
};

void reverse_list(LinkedList &list) {
    // 用tmp遍历list
    // list.head=NIL重置整个list
    Node *tmp = list.head;
    list.head = NIL;
    Node *next = NIL;
    while (tmp != NIL) {
        next = tmp->next;
        tmp->next = NIL;
        list.insert(tmp);
        tmp = next;
    }
}

int main () {
    LinkedList list;
    std::cout << list.head << std::endl;
    list.insert(new Node(12));
    std::cout << list.head << std::endl;
    list.insert(new Node(10));
    std::cout << list.head << std::endl;
    auto find = list.search(10);
    list.remove(find);
    std::cout << list.head << std::endl;

    std::cout << "=======test reverse======" << std::endl;
    LinkedList new_list;
    for (int i = 0; i < 10; ++i) {
        new_list.insert(new Node(rand() % 100));
    }
    new_list.output();
    reverse_list(new_list);
    new_list.output();
    return 0;
}