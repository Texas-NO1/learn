#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>

float getDis(float x1, float y1, float x2, float y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

struct T {
    int x;
    bool operator<(const T &t) const {
        return  x < t.x;
    }
};

int main () {
    std::priority_queue<T> queue;
    for (int i = 0; i < 10; ++i) {
        queue.push({i});
    }
    while (!queue.empty()) {
        std::cout << queue.top().x << std::endl;
        queue.pop();
    }

    std::vector<T> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back({rand()});
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < 10; ++i) {
        std::cout << vec[i].x << std::endl;
    }
    return 0;
}