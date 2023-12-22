#include <iostream>
#include <vector>

class HashTable {
private:
    // 标记bucket是否被占用/是否被删除，以实现所有int范围+删除情况
    // 0表示空
    // 1表示写了
    // 2表示写了但删了
    std::vector<int> label;
    std::vector<int> table;
    int n;
    int cnt;
    int hash_inner(int key) {
        return key % n;
    }
    int hash(int key, int i) {
        return (hash_inner(key) + i) % n;
    }
public:
    HashTable(int n) {
        table.resize(n);
        label.resize(n);
        this->n = n;
        this->cnt = 0;
    }
    bool insert(int key) {
        int i = 0;
        while (i < n) {
            int j = hash(key, i);
            // 没被写或被删除的位置可以写入
            if (label[j] == 0 || label[j] == 2) {
                table[j] = key;
                label[j] = 1;
                cnt++;
                return true;
            }
            i++;
        }
        return false;
    }

    int search(int key) {
        int i = 0;
        int j = 0;
        do {
            j = hash(key, i);
            // std::cout << "idx " << j << ", val " << table[j] << std::endl;
            // 没被删除且val等于key的位置返回
            if (label[j] == 1 && table[j] == key) return j;
            i++;
        } while (i < n && label[j] != 0);
        return -1;
    }

    bool remove(int key) {
        // 将目标的下标标记为删除
        int i = 0;
        int j = 0;
        do {
            j = hash(key, i);
            // 没被删除且val等于key的位置可以删除
            if (label[j] == 1 && table[j] == key) {
                label[j] = 2;
                cnt--;
                return true;
            }
            i++;
        } while (i < n && label[j] != 0);
        return false;
    }

    int size() {
        return cnt;
    }

    void output() {
        for (int i = 0; i < n; ++i) 
            std::cout << label[i] << "," << table[i] << std::endl;
        std::cout << std::endl;
    }

};

int main () {
    HashTable h(5);
    std::vector<int> org;
    for (int i = 0; i < 5; ++i)
        org.push_back(rand() % 1000);
    for (int i = 0; i < 20; ++i) {
        int op = rand() % 3;
        int num = org[rand() % org.size()];
        switch (op) {
            case 0:
                std::cout << "insert " << num << ", res " << h.insert(num) << std::endl;
                break;
            case 1:
                std::cout << "search " << num << ", res " << h.search(num) << std::endl;
                break;
            case 2:
                std::cout << "remove " << num << ", res " << h.remove(num) << std::endl;
                break;
        }
    }
    std::cout << "table size " << h.size() << std::endl;
    h.output();
    return 0;
}