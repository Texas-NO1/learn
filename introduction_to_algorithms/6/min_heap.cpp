#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    Node(int val) : val(val) {}

    int val = 0;
    Node *next = nullptr;
    // bool operator<(const Node *o) { // 不能对指针对象生效
    //     return val < o->val;
    // }

    // bool operator>(const Node *o) {
    //     return val > o->val;
    // }
};

bool less(const Node *a, const Node *b) {
    return a->val < b->val;
}
bool greater(const Node *a, const Node *b) {
    return a->val > b->val;
}

// bool operator<(const Node *a, const Node *b) { // 编译不能通过，gcc不能为内置类型重载运算符，指针类型本质上可能归于pointer类型(64bit)
//     return a->val < b->val;
// }

class Heap : public std::vector<Node*> {
public:
    // using std::vector<int>::vector; // 所有构造函数
    Heap(int length) : vector(length + 1) {
        heap_size = 0;
        this->length = length;
    }
    int heap_size;
    int length;
};

int left(int i) {
    return i << 1;
} 

int right(int i) {
    return (i << 1) + 1;
}

int parent(int i) {
    return i >> 1;
}

void min_heapify(Heap &A, int i) {
    while (true) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l <= A.heap_size && less(A[l], A[smallest])) smallest = l;
        if (r <= A.heap_size && less(A[r], A[smallest])) smallest = r;
        if (smallest != i) {
            std::swap(A[smallest], A[i]);
            i = smallest;
        } else {
            break;
        }
    }
}

void heap_sort(Heap &A) {
    for (int i = A.length; i >= 2; i--) {
        std::swap(A[i], A[1]);
        A.heap_size--;
        min_heapify(A, 1);
    }
}

void build_min_heap(Heap &A) {
    for (int i = A.heap_size / 2; i >= 1; --i) {
        min_heapify(A, i);
    }
}

Node* top(Heap &A) {
    return A[1];
} 


Node* top_and_pop(Heap &A) {
    if (A.heap_size < 1) {
        std::cout << "heap downflow\n";
    }
    Node* top = A[1];
    A[1] = A[A.heap_size];
    A.heap_size -= 1;
    min_heapify(A, 1);
    return top;
}

Node* insert(Heap &A, Node *node) {
    A.heap_size += 1;
    int i = A.heap_size;
    A[i] = node;
    while (i > 1 && less(node, A[parent(i)])) {
        // if (node->val == 11) std::cout << "i " << i << " v " << A[i]->val << ", ip " << parent(i) << " pv " << A[parent(i)]->val << std::endl;
        A[i] = A[parent(i)];
        i = parent(i);
        // if (node->val == 11) std::cout << "next round: i " << i << " v " << A[i]->val << ", ip " << parent(i) << " pv " << A[parent(i)]->val << std::endl;
    }
    A[i] = node;
}

void output(Node *node) {
    std::cout << "# ";
    while (node != nullptr) {
        std::cout << node->val;
        if (node->next != nullptr) std::cout << "->";
        node = node->next;
    }
    std::cout << std::endl;
}

int main () {
    // Node *ta = new Node(5);
    // Node *tb = new Node(10);
    // if (a < b) std::cout << "true";
    // else std::cout << "false";
    // if (tb > ta) std::cout << "true";
    // else std::cout << "false";

    int k = 10;
    std::vector<Node*> list;
    for (int i = 0; i < k; ++i) {
        int size = rand() % 10;
        std::vector<int> vec;
        for (int j = 0; j < size; ++j) {
            vec.push_back(rand() % 1000);
        }
        std::sort(vec.begin(), vec.end());
        Node head(0); // 空头节点
        Node *temp = &head;
        for (auto &v : vec) {
            temp->next = new Node(v);
            temp = temp->next;
        }
        output(head.next);
        list.push_back(head.next);
    }

    Heap a(k);
    Node new_list(0);
    Node *temp = &new_list;
    for (auto &l : list) {
        insert(a, l);
        std::cout << "heap: ";
        for (int i = 1; i <= a.heap_size; ++i) std::cout << a[i]->val << " ";
        std::cout << std::endl;
    }
    while (a.heap_size != 0) {
        Node *top_node = top_and_pop(a);
        // std::cout << "pop " << top_node->val << "\n";
        Node *next_input_node = top_node->next;
        top_node->next = nullptr;
        temp->next = top_node;
        temp = temp->next;
        if (next_input_node != nullptr) insert(a, next_input_node);
    }
    output(new_list.next);
    return 0;
}