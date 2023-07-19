#include <iostream>
#include <vector>
#include "utils.hpp"

void boob_sort(std::vector<int> &A, int start, int end) {
    for (int i = start; i <= end - 1; ++i) {
        for (int j = end; j >= i + 1; --j) {
            if (A[j] < A[j - 1]) {
                std::swap(A[j], A[j - 1]);
            }
        }
    }
}

int main () {
    std::vector<int> test3{31,41,59,26,41,58};
    boob_sort(test3, 0, test3.size() - 1);
    output(test3);
    return 0;
}