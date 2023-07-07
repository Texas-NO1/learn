#include <iostream>
#include <vector>
#include <cassert>

int search(std::vector<int> &vec, int l, int r, int key) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (vec[mid] == key) return mid;
        else if (vec[mid] > key) r = mid - 1;
        else l = mid + 1; 
    }
    return -1;
}

void merge(std::vector<int> &vec, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = vec[p + i];
    for (int i = 0; i < n2; ++i) R[i] = vec[q + i + 1];

    int i = 0, j = 0;
    for (int k = p; k <= r; ++k) {
        if (i < n1 && (L[i] < R[j] || j >= n2)) {
            vec[k] = L.at(i);
            ++i;
        } else {
            vec[k] = R.at(j);
            ++j;
        }
    }
}

void merge_sort(std::vector<int> &vec, int p, int r) {
    if (p < r) {
        int mid = (p + r) / 2;
        merge_sort(vec, p, mid);
        merge_sort(vec, mid + 1, r);
        merge(vec, p, mid, r);
    }
}

bool sum_x(std::vector<int> &vec, int target) {

    merge_sort(vec, 0, vec.size() - 1);
    
    for (int i = 0; i < vec.size(); ++i) {
        int idx = search(vec, i + 1, vec.size() - 1, target - vec[i]);
        if (idx != -1) {
            std::cout << vec[i] << "+" << vec[idx] << "=" << target << std::endl;
            return true;
        }
    }
    return false;
}

void output(std::vector<int> &vec) {
    int n = vec.size();
    for (int i = 0; i < n; ++i) {
        assert(i == 0 || vec[i] >= vec[i - 1]);
        std::cout << vec[i] << " ";
    }
}

void random(std::vector<int> &vec, int n) {
    vec.resize(n);
    for (int i = 0; i < n; ++i) vec[i] = rand() % 100000;
}

int main () {

    std::vector<int> test;
    random(test, 500);

    for (int i = 0; i < test.size() - 1; ++i) {
        for (int j = i + 1; j < test.size() - 1; ++j) {
            assert(sum_x(test, test[i] + test[j]));
        }
    }
    return 0;
}