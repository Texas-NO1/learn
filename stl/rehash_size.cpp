#include <unordered_set>
#include <iostream>
#include <vector>

int main () {
    // 1,13,29,59,127,257,541,1109,2357,5087,10273,20753,42043,85229,172933,351061,712697,1447153,2938679,5967347,12117689,
    // 初始bucket大小为1，后续bucket大小为递增的质数
    // 超过上一次的bucket大小时，立即进行扩容（stl底层的负载因子为1.0）
    std::unordered_set<int> map;
    int bucket = map.bucket_count();
    std::cout << map.size() << "," << map.bucket_count() << std::endl;
    for (int i = 0; i < 10000000; ++i) {
        map.insert(i);
        if (bucket != map.bucket_count()) {
            std::cout << map.size() << "," << map.bucket_count() << std::endl;
        }
        bucket = map.bucket_count();
    }
    return 0;
}