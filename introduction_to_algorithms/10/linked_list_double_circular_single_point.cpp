#include <iostream>
#include <sstream>

/**
 * 双向链表，只有一个np=prev XOR next，替代原来实现的两个指针prev和next
 * 实现原理
 * 1. a^b^a = b
 * 2. head节点的prev为0，tail节点的next为0
 * 3. 因此可以计算得到head.next=head.prev ^ head.next ^ head.prev = head.np ^ 0
*/

#define NIL nullptr

struct Node {
    int key;
    uint64_t np = 0;
    Node() = default;
    Node(int k) : key(k) {};
};

struct List {
    Node *head; // head为虚拟节点，不存放数据，只用来获取第一个节点位置
    Node *tail; // tail为虚拟节点，不存放数据，只用来获取最后一个节点位置

    List() {
        head = new Node();
        tail = new Node();
        head->np = get_np(0, tail);
        tail->np = get_np(head, 0);
    }

    Node* get_prev(Node *cur, Node *next) {
        return (Node*)(cur->np ^ (uint64_t)next);
    }

    Node* get_next(Node *cur, Node *prev) {
        return (Node*)(cur->np ^ (uint64_t)prev);
    }

    uint64_t get_np(Node* prev, Node *next) {
        return (uint64_t)prev ^ (uint64_t)next;
    }

    Node* search(int k) {
        Node *x = get_next(head, 0);
        Node *prev = head;
        while (x != tail && x->key != k) {
            Node *next = get_next(x, prev);
            prev = x;
            x = next;
        }
        if (x == tail) return NIL;
        return x;
    }

    void insert(Node *target) {
        Node *head_next = get_next(head, 0);
        Node *head_next_next = get_next(head_next, head);
        // std::cout << "cur: " << single_node_str(target) << std::endl;
        // std::cout << "head: " << single_node_str(head) << std::endl;
        // std::cout << "head's next: " << single_node_str(head_next) << std::endl;
        // std::cout << "head's next's next: " << single_node_str(head_next_next) << std::endl;
        head->np = get_np(0, target);
        head_next->np = get_np(target, head_next_next);
        target->np = get_np(head, head_next);
    }

    void remove(Node *target) {
        Node *x = get_next(head, 0);
        Node *prev = head;
        while (x != target) {
            Node *next = get_next(x, prev);
            prev = x;
            x = next;
        }
        Node *next = get_next(x, prev);
        Node *next_next = get_next(next, x);
        Node *prev_prev = get_prev(prev, x);
        prev->np = get_np(prev_prev, next);
        next->np = get_np(prev, next_next);
    }

    std::string single_node_str(Node *x) {
        std::stringstream ss;
        if (x == head) ss << "head,";
        else if (x == tail) ss << "tail";
        else if (x == NIL) ss << "NIL,";
        else ss << x->key << ",";
        return ss.str();
    }

    void output() {
        Node *x = head;
        Node *prev = 0;
        while (x != 0) {
            std::cout << single_node_str(x);
            Node *next = get_next(x, prev);
            prev = x;
            x = next;
        }
        std::cout << std::endl;
    }

    void reverse() {
        // 使用三个数交换值
        Node *tmp = head;
        head = tail;
        tail = tmp;
        // 使用与或运算交换值
        // head = (Node*)((uint64_t)head ^ (uint64_t)tail);
        // tail = (Node*)((uint64_t)head ^ (uint64_t)tail);
        // head = (Node*)((uint64_t)head ^ (uint64_t)tail);
    }
};

int main () {
    List l;
    for (int i = 0; i < 10; ++i) {
        l.insert(new Node(i));
    }
    l.output();
    l.reverse();
    l.output();
    Node* res = l.search(5);
    std::cout << "remove " << l.single_node_str(res) << std::endl;
    l.remove(res);
    l.output();
    return 0;
}