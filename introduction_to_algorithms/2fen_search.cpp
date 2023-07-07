#include <iostream>
#include <vector>

int search(std::vector<int> &vec, int key) {
    int l = 0, r = vec.size() - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (vec[mid] == key) {
            return mid;
        } else if (vec[mid] > key) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int main () {
    std::vector<int> vec = {2, 4, 6, 22, 54, 59, 84, 223, 46454};
    for (auto &t : vec) std::cout << search(vec, t) << std::endl;

    return 0;
}