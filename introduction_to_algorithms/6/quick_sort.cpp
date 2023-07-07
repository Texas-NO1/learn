#include <iostream>
#include <vector>

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

void quick_sort(std::vector<int> &A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

int main () {
    std::vector<int> A;
    for (int i = 0; i < 10; ++i) A.push_back(rand() % 1000);
    quick_sort(A, 0, A.size() - 1);
    for (int i = 0; i < 10; ++i) std::cout << A[i] << ",";
    std::cout << std::endl;
    return 0;
}