#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <chrono>


std::tuple<int, int, int> brute_force(std::vector<int> &A, int low, int high) {
    int max_left = 0, max_right = 0, sum_max = INT32_MIN;
    for (int i = low; i <= high; ++i) {
        int sum = 0;
        for (int j = i; j <= high; ++j) {
            sum += A[j];
            if (sum >= sum_max) {
                sum_max = sum;
                max_left = i;
                max_right = j;
            }
        }
    }
    return {max_left, max_right, sum_max};
}

std::tuple<int, int, int> find_max_crossing_subarray(std::vector<int> &A, int low, int mid, int high) {
    int left_sum = INT32_MIN;
    int sum = 0;
    int max_left = -1;
    for (int i = mid; i >= low; --i) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = INT32_MIN;
    sum = 0;
    int max_right = -1;
    for (int i = mid + 1; i <= high; ++i) {
        sum += A[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }
    return {max_left, max_right, left_sum + right_sum};
}

std::tuple<int, int, int> find_maximum_subarray(std::vector<int> &A, int low, int high) {
    if (low == high) {
        return {low, high, A[low]};
    } else {
        int mid = (low + high) / 2;
        std::tuple<int, int, int> left = find_maximum_subarray(A, low, mid);
        std::tuple<int, int, int> right = find_maximum_subarray(A, mid + 1, high);
        std::tuple<int, int, int> cross = find_max_crossing_subarray(A, low, mid, high);
        if (std::get<2>(left) >= std::get<2>(right) && std::get<2>(left) >= std::get<2>(cross)) {
            return left;
        } else if (std::get<2>(right) >= std::get<2>(left) && std::get<2>(right) >= std::get<2>(cross)) {
            return right;
        } else {
            return cross;
        }
    }
    return {-1, -1, -1};
}

std::tuple<int, int, int> find_maximum_subarray_with_slice(std::vector<int> &A, int low, int high, int slice) {
    if (high - low >= slice) {
        return brute_force(A, low, high);
    } else {
        find_maximum_subarray(A, low, high);
        std::sort()
    }
}

void rand_array(std::vector<int> &A, int n) {
    for (int i = 0; i < n; ++i) {
        int r = rand() % 1000;
        if (rand() % 2) r = -r;
        A.push_back(r);
    }
}



int main () {
    // std::vector<int> array = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    srand(time(0));
    float diff = 0;
    // int n = 10;
    // while (diff >= 0) {
    //     std::vector<int> array;
    //     rand_array(array, n += 10);
    //     auto t0 = std::chrono::high_resolution_clock::now();
    //     auto res = find_maximum_subarray(array, 0, array.size() - 1);
    //     auto t1 = std::chrono::high_resolution_clock::now();
    //     std::cout << std::get<0>(res) << "-" << std::get<1>(res) << " = " << std::get<2>(res) << std::endl;
    //     auto t2 = std::chrono::high_resolution_clock::now();
    //     res = brute_force(array, 0, array.size() - 1);
    //     auto t3 = std::chrono::high_resolution_clock::now();
    //     std::cout << std::get<0>(res) << "-" << std::get<1>(res) << " = " << std::get<2>(res) << std::endl;
    //     diff = std::chrono::duration<float>(t1 - t0).count() - std::chrono::duration<float>(t3 - t2).count();
    //     std::cout << "nlgn - n^2 = " << diff << "s" << std::endl;
    // }
    // std::cout << "when n = " << n << " nlgn fast then n^2" << std::endl; // get 40

    int n = 1000;
    std::vector<int> array;
    rand_array(array, n);
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        auto res = find_maximum_subarray(array, 0, array.size() - 1);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << std::get<0>(res) << "-" << std::get<1>(res) << " = " << std::get<2>(res) << std::endl;
        std::cout << "slice 0 take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
    }
    {
        int slice = 0;
        auto t0 = std::chrono::high_resolution_clock::now();
        auto res = find_maximum_subarray_with_slice(array, 0, array.size() - 1, slice);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << std::get<0>(res) << "-" << std::get<1>(res) << " = " << std::get<2>(res) << std::endl;
        std::cout << "slice " << slice << " take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
    }
    return 0;
}