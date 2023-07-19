#include <iostream>
#include <vector>

// 快排思路：
// partition维护了4个区域，[p,i],[i+1,j][j+1,r-1],[r]
// 1.[p,i]<=x
// 2.[i+1,j]>x
// 3.[j+1,r-1]无限制
// 4.[r]=x
// 初始i=p-1，[p,p-1]表示初始<=x的集合为空
// 循环完成后[j+1,r-1]消失，只剩3个区域，[p,i]<=x,[i+1,r-1]>x,[r]=x
// [p,i]都<=x，所以A[r]可以与A[i+1]交换位置，i+1即落入正确位置，使最后变成3个区域
// 1.[p,i]<=x
// 2.[i+1]=x，x已落入正确位置，返回i+1
// 3.[i+2,r]>x

int partition(std::vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j) {
        if (A[j] <= x) {
            i = i + 1;
            std::swap(A[j], A[i]);
        }
    }
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

// 基础快排
void quick_sort(std::vector<int> &A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

int partition_random(std::vector<int> &A, int p, int r) {
    int i = rand() % (r - p + 1) + p;
    std::swap(A[r], A[i]);
    return partition(A, p, r);
}

// 随机基准快排
void quick_sort_radom(std::vector<int> &A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

// 尾递归优化快排
void tail_recursive_quick_sort(std::vector<int> &A, int p, int r) {
    while (p < r) {
        int q = partition(A, p, r);
        tail_recursive_quick_sort(A, p, q - 1);
        p = q + 1;
    }
}

int main () {
    std::vector<int> A;
    for (int i = 0; i < 10; ++i) A.push_back(rand() % 1000);
    // quick_sort(A, 0, A.size() - 1);
    // quick_sort_radom(A, 0, A.size() - 1);
    tail_recursive_quick_sort(A, 0, A.size() - 1);
    for (int i = 0; i < 10; ++i) std::cout << A[i] << ",";
    std::cout << std::endl;
    return 0;
}