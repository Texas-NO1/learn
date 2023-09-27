#include <iostream>
#include <vector>
#include <unordered_set>

// T是一个特别大的数组，无法初始化
// 用栈的思路
// 使用辅助数组S，保存插入的实际key
// 使用辅助数组S'，保存插入的实际对象
// 而T存放插入数据在S/S'中的下标

struct Node {
    int key;
    int value;
};

std::vector<int> T(1000);
std::vector<int> S(1,0); // 初始化一个位置
std::vector<Node*> S_s(1,nullptr);// 初始化一个位置

Node* direct_address_search(int k) {
    if (T[k] > 0 && T[k] < S.size() && k == S[T[k]]) {
        return S_s[T[k]];
    }
    return nullptr;
}

void direct_address_insert(Node* x)  {
    T[x->key] = S.size();
    S.push_back(x->key);
    S_s.push_back(x);
}

void direct_address_delete(int k) {
    int top = S.size() - 1;
    S[T[k]] = S[top];
    S_s[T[k]] = S_s[top];
    T[S[top]] = T[k]; // 原top在T中的值改变
    S.pop_back();
    S_s.pop_back();
    T[k] = 0;
}

int main () {
    std::unordered_set<int> keys;
    std::cout << "input: ";
    for (int i = 0; i < 10; ++i) {
        Node *n = new Node();
        n->key = rand() % 1000;
        keys.insert(n->key);
        n->value = rand();
        direct_address_insert(n);
        std::cout << "(" << n->key << "," << n->value << "),";
    }
    std::cout << std::endl;
    // std::vector<int> test_keys = {777, 386, 383};
    for (auto key : keys) {
        Node* n = direct_address_search(key);
        std::cout << "search: " << key << ", res: (" << n->key << "," << n->value << ")," << std::endl;
        int before_top = S[S.size() - 1];
        direct_address_delete(key);
        std::cout << "delete: " << key << ", before top " << before_top << ", cur top " << S[S.size() - 1] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "S " << S.size() - 1 << ", S_s " << S_s.size() - 1 << std::endl;
    return 0;
}