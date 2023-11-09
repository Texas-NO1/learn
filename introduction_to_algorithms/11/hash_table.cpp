#include <iostream>
#include <vector>
#include <cmath>


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
// h(k) = ((ak + b) mod P) mod m
// P为一个比所有k都大的素数，m随意
// a属于[1,p-1]
// b属于[0, p-1]
struct UniversalHash{
    uint64_t P = 2;
    uint64_t a = 1;
    uint64_t b = 1;
    UniversalHash(uint64_t input_P = 1073741789) : P(input_P) {
        uint64_t a = (rand() % (P - 1)) + 1;
        uint64_t b = rand() % P;
    }
    uint64_t operator()(const int &k) {
        return  (a * k + b ) % P;
    }
};

// 除法散列，h(k) = k mod m
// 散列效果如何在于m的选择（hash表大小），对内置自然数类型的c++底层实现均为除法散列，如int/unit64_t
struct DivisionHash {
    uint64_t operator()(const int &k) {
        return  k;
    }
};

// 乘法散列，h(k) = floor(m*(k*A mod 1)) 
// 0<A<1, k*A mod 1表示取乘积的小数部分
// 散列效果如何在于A的选择，m随意，选黄金分割率 (sqrt(5)-1)/2
struct MultiplicationHash {
    uint64_t operator()(const int &k) {
        float A = (std::sqrt(5) - 1) / 2;
        float res = 0;
        // printf("%.10f %.10f\n", res, std::modf(A * k, &res));
        return std::modf(A * k, &res);
    }
};

// 默认hash就是除法散列
template<>
struct DefaultHash<int>{
    uint64_t operator()(int t) {
        return t;
    }
};


template<typename T, typename Hash = DefaultHash<T>>
struct HashTable {
    std::vector<List<T>> table;
    Hash hash; // 因为全域随机散列函数需要初始化确定，所以只能构建一次
    int _size = 0;
    HashTable(int initsize) {
        table.resize(initsize);
        hash = Hash();
    }
    int size() {
        return _size;
    }
    uint64_t hash_code (const T &x){
        return hash(x) % table.size();
        // return Hash()(x) % table.size(); // 非全域随机hash可以每次创建（c++底层实现）
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
    // HashTable<int, DivisionHash> table(n); // 除法
    // HashTable<int, MultiplicationHash> table(n); // 乘法
    HashTable<int, UniversalHash> table(n); // 全域
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