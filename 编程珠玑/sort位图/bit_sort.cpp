#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>

const int MAX_SIZE = 100000;
const int MAX_NUMER = 100000000;

void generateNums() {
    std::cout << "gen num start\n";
    std::ofstream file("nums.txt");
    int max_nums = MAX_SIZE;
    while (max_nums) {
        file << rand() % MAX_NUMER << "\n";
        --max_nums;
    }
    std::cout << "gen num over\n";
}

void stlSort() {
    std::cout << "stl sort num start\n";
    time_t t0 = time(0);
    int *nums = new int[MAX_SIZE];
    std::ifstream in_file("nums.txt");
    int cur = 0;
    while (!in_file.eof()) {
        int temp = 0;
        in_file >> temp;
        nums[cur++] = temp;
    }
    in_file.close();
    time_t t1 = time(0);
    std::cout << "sort\n";
    std::sort(nums, nums + MAX_SIZE);
    time_t t2 = time(0);

    std::ofstream out_file("stl_sort_nums.txt");
    for (int i = 0; i < MAX_SIZE; ++i) {
        out_file << nums[i] << '\n';
    }
    out_file.close();
    time_t t3 = time(0);
    std::cout << "stl sort num over\n";
    std::cout << "stl sort input " << t1 - t0 << ", sort " << t2 - t1 << ", output " << t3 - t2 << " take time " << t3 - t0 << "\n";
    delete nums;
}

void bitSort() {
    std::cout << "bit sort num start\n";
    time_t t0 = time(0);
    bool *nums = new bool[MAX_NUMER];
    for (int i = 0; i < MAX_NUMER; ++i) {
        nums[i] = false;
    }
    std::ifstream in_file("nums.txt");
    while (!in_file.eof()) {
        int temp = 0;
        in_file >> temp;
        nums[temp] = true;
    }
    in_file.close();
    time_t t1 = time(0);

    std::ofstream out_file("bit_sort_nums.txt");
    for (int i = 0; i < MAX_NUMER; ++i) {
        if (nums[i]) {
            out_file << i << '\n';
        }
    }
    out_file.close();
    time_t t2 = time(0);
    std::cout << "bit sort num over\n";
    std::cout << "bit sort input " << t1 - t0 << ", output " << t2 - t1 << " take time " << t2 - t0 << "\n";
    delete nums;
}

int main () {
    std::cout << "start\n";
    time_t t0 = time(0);
    // bitSort();
    stlSort();
    time_t t1 = time(0);
    std::cout << "over, total time " << t1 - t0 << "\n";
    return 0;
}