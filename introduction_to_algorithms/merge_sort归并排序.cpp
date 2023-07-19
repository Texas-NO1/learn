#include <iostream>
#include <vector>
#include <cassert>

void merge(std::vector<int> &A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    std::vector<int> L(n1 + 1), R(n2 + 1);
    int i, j;
    for (i = 1; i <= n1; ++i) L[i] = A[p + i - 1];
    for (j = 1; j <= n2; ++j) R[j] = A[q + j];

    i = 1, j = 1;
    for (int k = p; k <= r; ++k) {
        if (i <= n1 && (L[i] <= R[j] || j > n2)) {
            A[k] = L.at(i);
            i = i + 1;
        } else {
            A[k] = R.at(j);
            j = j + 1;
        }
    }
}

// void merge(std::vector<int> &A, int p, int q, int r) {
//     int n1 = q - p + 1;
//     int n2 = r - q;

//     std::vector<int> L(n1 + 2), R(n2 + 2);
//     int i, j;
//     for (i = 1; i <= n1; ++i) L[i] = A[p + i - 1];
//     for (j = 1; j <= n2; ++j) R[j] = A[q + j];
//     L[n1 + 1] = INT32_MAX;
//     R[n2 + 1] = INT32_MAX;

//     i = 1, j = 1;
//     for (int k = p; k <= r; ++k) {
//         if (L[i] <= R[j]) {
//             A[k] = L[i];
//             i = i + 1;
//         } else {
//             A[k] = R[j];
//             j = j + 1;
//         }
//     }
// }

void merge_sort(std::vector<int> &A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main () {
    int n = 1001;
    std::vector<int> A(n + 1, 0);
    for (int i = 1; i <= n; ++i) A[i] = rand() % 100000;
    merge_sort(A, 1, n);
    for (int i = 1; i <= n; ++i) {
        assert(A[i] >= A[i - 1]);
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}