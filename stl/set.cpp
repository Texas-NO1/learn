#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>

struct Point {
    float x;
    float y;
    bool operator<(const Point &p) const {
        std::cout << "cmp x, y" << std::endl;
        if (std::fabs(x - p.x) > 1e-7) return x < p.x;
        std::cout << "same x, cmp y" << std::endl;
        if (std::fabs(y - p.y) > 1e-7) return y < p.y;
        std::cout << "same x, same y" << std::endl;
        return false;
    }
};

int main () {
    std::set<Point> s;
    Point x;
    x.x = 3;
    x.y = 5;
    Point y;
    y.x = 3;
    y.y = 5;
    s.insert(x);
    s.insert(y);
    return 0;
}