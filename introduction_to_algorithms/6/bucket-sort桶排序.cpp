#include <iostream>
#include <vector>
#include <cmath>

// 桶排序思路：
// 假设输入数组服从均匀分布，平均情况下时间复杂度O(n)
// 设输入数组大小为n，元素都在[0,1)之间，[0,1)拆分为n个链表（桶），第i个数字插入第floor(nA[i])个桶中进行插入排序
// 最后按顺序对[0,n-1]桶中的数据拼接起来即进行排序。
// 只要每个桶内元素的平方和与n成线性关系则复杂度O(n)

template<typename T>
struct Node {
    T value;
    Node *next;
    Node():value(T()), next(nullptr){}
    Node(const T &t):value(t), next(nullptr){}
};

void bucket_sort(std::vector<float> &A) {
    int n = A.size();
    std::vector<Node<float>> buckets(n);
    auto insert_bucket = [&](Node<float> &bucket, float value) -> void {
        Node<float> *temp = &bucket;
        while (temp->next && temp->next->value <= value) { // 找到第一个next > value的位置
            temp = temp->next;
        }
        Node<float> *new_node = new Node<float>(value);
        new_node->next = temp->next;
        temp->next = new_node;
    };
    for (int i = 0; i < n; ++i) {
        int idx = std::floor(A[i] * n);
        insert_bucket(buckets[idx], A[i]);
    }
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        Node<float> *temp = &buckets[i];
        std::cout << "bucket " << i << ":";
        while (temp->next) {
            std::cout << temp->next->value << ",";
            A[cur++] = temp->next->value;
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

int main () {
    int n = 15, k = 1000;
    std::vector<float> A;
    int pre = 0;
    for (int i = 0; i < n; ++i) {
        int cur = 0;
        if (pre != 0 && !(rand() % 3)) cur = pre; // 1/3概率数字会重复
        else cur = rand() % k;
        A.push_back((float)cur / (float)k);
        pre = cur;
    }
    for (int i = 0; i < n; ++i) std::cout << A[i] << ",";
    std::cout << std::endl;
    bucket_sort(A);
    for (int i = 0; i < n; ++i) std::cout << A[i] << ",";
    std::cout << std::endl;
    return 0;
}