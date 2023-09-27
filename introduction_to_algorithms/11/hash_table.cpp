#include <iostream>
#include <vector>


template<typename T> 
struct Node {
    Node* prev = nullptr;
    Node* next = nullptr;
    T value;
    Node() = default;
    Node(const T &t) : value(t) {}
};

template<typename T>
struct List {
    Node<T> *head = nullptr;
    Node<T>* search(T k) {
        Node<T> *tmp = head;
        while (tmp != nullptr && tmp->value != k) {
            tmp = tmp->next;
        }
        return tmp;
    }
    void insert(Node<T> *x) {
        x->next = head;
        x->prev = nullptr;
        if (head != nullptr) {
            head->prev = x;
        }
        head = x;
    }
    void remove(Node<T> *x) {
        if (x->prev != nullptr) {
            x->prev->next = x->next;
        } else { // 前驱节点为空的节点就是head节点，head节点被删就把head的next节点作为head节点
            head = x->next;
        }
        if (x->next != nullptr) {
            x->next->prev = x->prev;
        }
    }
};

template<typename T>
struct DefaultHash{
    uint64_t operator()(const T &t) {
        std::cerr << "no operator for type " << typeid(T).name();
        return 0;
    }
};

// 全域散列，初始化时使用随机算法生成散列函数
struct UniversalHash{
    uint64_t P = 2;
    uint64_t a = 1;
    uint64_t b = 1;
    UniversalHash(uint64_t input_P = 1073741789) : P(input_P) {
        uint64_t a = rand() % P;
        uint64_t b = (rand() % (P - 1)) + 1;
    }
    uint64_t operator()(const int &k) {
        return  (a * k + b ) % P;
    }
};

template<>
struct DefaultHash<int>{
    uint64_t operator()(int t) {
        return t;
    }
};


template<typename T, typename Hash = DefaultHash<T>>
struct HashTable {
    std::vector<List<T>> table;
    int _size = 0;
    HashTable(int initsize) {
        table.resize(initsize);
    }
    int size() {
        return _size;
    }
    uint64_t hash_code (const T &x){
        return Hash()(x) % table.size();
    }
    bool search(const T &x) {
        return table[hash_code(x)].search(x) !=  nullptr;
    }
    void insert(const T &x) {
        Node<T> *new_node = new Node<T>(x);
        table[hash_code(x)].insert(new_node);
        _size++;
    }
    void remove(const T &x) {
        auto res = table[hash_code(x)].search(x);
        if (res == nullptr) return;
        // std::cout << "to delete " << x;
        table[hash_code(x)].remove(res);
        _size--;
    }
};

int main () {
    int n = 50, m = 150, max = 300;
    HashTable<int, UniversalHash> table(n);
    std::vector<int> total;
    std::cout << "\ninsert ";
    for (int i = 0; i < m; ++i) {
        total.push_back(rand() % max);
        table.insert(total.back());
        std::cout << total.back() << ",";
    }
    std::cout << "\ntotal " << table.size() << "\n";
    std::cout << "\nsearch ";
    for (auto t : total) {
        std::cout << table.search(t) << ",";
    }
    std::cout << "\ndelete ";
    for (auto t : total) {
        table.remove(t);
    }
    std::cout << "\ntotal " << table.size() << "\n";
    std::cout << "\nsearch ";
    for (auto t : total) {
        std::cout << table.search(t) << ",";
    }
    return 0;
}