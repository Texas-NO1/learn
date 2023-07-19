#include <iostream>
#include <vector>
#include <cmath>

// 基数排序思路：
// 对d位的数字，每位数字有k个选择，从第1位到第d位对每位数字进行单独的稳定排序（如计数排序），所有位排序完则整个数组排序完成
// 理解：每位数字的权值不同，从权值低的开始到权值高的位排序

void count_sort_digit(const std::vector<int> &A, std::vector<int> &B, int digit_max, int digit_idx) {
    std::vector<int> C(digit_max, 0);
    int step = std::pow(digit_max, digit_idx);
    auto get_digit = [&](int x) -> int {
        return (x % step) / (step / digit_max);
    };
    for (int i = 0; i < A.size(); ++i) C[get_digit(A[i])]++;
    for (int i = 1; i < C.size(); ++i) C[i] += C[i - 1];
    for (int i = A.size() - 1; i >= 0; --i) {
        B[C[get_digit(A[i])] - 1] = A[i];
        C[get_digit(A[i])]--;
    }
}

void radix_sort(std::vector<int> &A, int d, int digit_max) {
    std::vector<int> B(A.size(), 0);
    std::cout << "original: ";
    for (int i = 0; i < A.size(); ++i) std::cout << A[i] << ",";
    std::cout << std::endl;
    for (int i = 1; i <= d; ++i) {
        count_sort_digit(A, B, digit_max, i);
        A.swap(B);
        for (int i = 0; i < A.size(); ++i) std::cout << A[i] << ",";
        std::cout << std::endl;
    }
}


int main () {
    int n = 10, k = 1000;
    int d = std::log10(k); // 3位数字
    std::vector<int> A;
    int pre = 0;
    for (int i = 0; i < 10; ++i) {
        int cur = 0;
        if (pre != 0 && !(rand() % 3)) cur = pre; // 1/3概率数字会重复
        else cur = rand() % k;
        A.push_back(cur);
        pre = cur;
    }
    // count_sort(A, B, k);
    radix_sort(A, d, 10);
    for (int i = 0; i < 10; ++i) std::cout << A[i] << ",";
    std::cout << std::endl;
    return 0;
}