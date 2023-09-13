#include <iostream>
#include <vector>
#include <cassert>

int partition(std::vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

int randomized_partition(std::vector<int> &A, int p, int r) {
    int i = rand() % (r - p + 1) + p;
    std::swap(A[i], A[r]);
    return partition(A, p, r);
}

int randomized_select(std::vector<int> &A, int p, int r, int i) {
    if (p == r) {
        return A[p];
    }
    int q = randomized_partition(A, p, r);
    int k = q - p + 1;
    if (k == i) {
        return A[q];
    } else if (i < k) {
        return randomized_select(A, p, q - 1, i);
    } else {
        return randomized_select(A, q + 1, r, i - k);
    }
}

int main () {
    std::vector<int> A;
    srand(time(0));
    for (int i = 0; i < 10; ++i) A.push_back(rand() % 1000);
    // quick_sort(A, 0, A.size() - 1);
    // quick_sort_radom(A, 0, A.size() - 1);
    int k = rand() % A.size();
    int v = randomized_select(A, 0, A.size() - 1, k);
    std::cout << k << " : " << v << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << A[i] << ",";
        assert((i < k && A[i] <= v) || (i >= k && A[i] > v)); //前k个都<=v, 后n-k个都>v
    }
    std::cout << std::endl;
    return 0;
}