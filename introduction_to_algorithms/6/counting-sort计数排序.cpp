#include <iostream>
#include <vector>

// 计数排序思路：
// 1.统计A所有数字出现次数到C
// 2.对C从前往后计算<=i的累计数字，即新排序数组的中i所在的下标(+1)
// 3.对A从后往前，C[A[j]]即<=A[j]的个数，即A[j]在B中的下标
// 对于C中下标i，由于计数必须是从0到n增大，因此n一定是i在A中最后一次出现的位置的下标

void count_sort(std::vector<int> &A, std::vector<int> &B, int k) {
    std::vector<int> C(k, 0);
    // 计数
    for (int i = 0; i < A.size(); ++i) {
        C[A[i]]++;
    }
    // 累计，计算i位置有多少<=i
    for (int i = 1; i < C.size(); ++i) {
        C[i] = C[i] + C[i - 1];
    }
    // 从后往前填充下标
    for (int i = A.size() - 1; i >= 0; --i) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--; // 重复一个则下标减少
    }
}

int main () {
    int n = 10, k = 1000;
    std::vector<int> A, B(n, 0);
    int pre = 0;
    for (int i = 0; i < 10; ++i) {
        int cur = 0;
        if (pre != 0 && !(rand() % 3)) cur = pre; // 1/3概率数字会重复
        else cur = rand() % k;
        A.push_back(cur);
        pre = cur;
    }
    count_sort(A, B, k);
    for (int i = 0; i < 10; ++i) std::cout << B[i] << ",";
    std::cout << std::endl;
    return 0;
}