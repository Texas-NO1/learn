#include <iostream>
#include <vector>

void partition (std::vector<int> &arr, int left, int right) {
    int l = left, r = right;
    if (l >= r) return;
    int pos = l;
    int value = arr[pos];
    while (l < r) {
        while (l < r && value <= arr[r]) 
            r--;
        arr[pos] = arr[r];
        pos = r--;
        while (l < r && value >= arr[l])
            l++;
        arr[pos] = arr[l];
        pos = l++;
    }
    arr[pos] = value;
    partition(arr, left, pos - 1);
    partition(arr, pos + 1, right);
}

int main () {
    std::vector<int> vec = {4, 2, 14, 53, 632, 62, 2, 4, 0};
    partition(vec, 0, vec.size() - 1);
    for (auto &t : vec) {
        std::cout << t << " ";
    }
    std::cout << std::endl;
    return 0;
}