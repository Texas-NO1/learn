#include <iostream>
#include <vector>
#include "utils.hpp"

void insert_sort(std::vector<int> &vec) {
    for (int j = 1; j < vec.size(); ++j) {
        int key = vec[j];
        int i = j - 1;
        while (i >= 0 && vec[i] > key) {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}

void insert_sort_recursion(std::vector<int> &vec, int p, int r) {
    if (p >= r) return;
    insert_sort_recursion(vec, p, r - 1);
    int i = r - 1;
    int key = vec[r];
    while (i >= 0 && vec[i] > key) {
        vec[i + 1] = vec[i];
        i--;
    }
    vec[i + 1] = key;
}

void insert_sort_less(std::vector<int> &vec) {
    for (int j = 1; j < vec.size(); ++j) {
        int key = vec[j];
        int i = j - 1;
        while (i >= 0 && vec[i] < key) {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}


int main () {

    std::vector<int> test{5,2,4,6,1,3};
    insert_sort(test);
    output(test);

    std::vector<int> test1{31,41,59,26,41,58};
    insert_sort(test1);
    output(test1);

    std::vector<int> test2{31,41,59,26,41,58};
    insert_sort_less(test2);
    output(test2);

    std::vector<int> test3{31,41,59,26,41,58};
    insert_sort_recursion(test3, 0, test3.size() - 1);
    output(test3);
    return 0;
}