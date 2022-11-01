#include <shared_mutex>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

class IDPointerMap {
public:
    // 外界只能获得weak指针，通过if判断是否能获取真实值
    static std::shared_ptr<std::string> getPointer(const std::string &id) {
        {
            std::shared_lock<std::shared_mutex> rlock(id2pointer_mux);
            if (id2pointer.find(id) != id2pointer.end()) {
                return id2pointer[id];
            }
        }
        {
            std::unique_lock<std::shared_mutex> wlock(id2pointer_mux);
            id2pointer[id] = std::shared_ptr<std::string>(new std::string(id));
            return id2pointer[id];
        }
    }
    static bool erase(const std::string &id) {
        std::unique_lock<std::shared_mutex> wlock(id2pointer_mux);
        id2pointer.erase(id);
    }
    static bool erase(const std::vector<std::string> &ids) {
        std::unique_lock<std::shared_mutex> wlock(id2pointer_mux);
        for (auto &id : ids) id2pointer.erase(id);
    }
    static void clear() {
        std::unique_lock<std::shared_mutex> wlock(id2pointer_mux);
        id2pointer.clear();
    }
private:
    static std::shared_mutex id2pointer_mux;
    static std::unordered_map<std::string, std::shared_ptr<std::string>> id2pointer;
};
std::shared_mutex IDPointerMap::id2pointer_mux;
std::unordered_map<std::string, std::shared_ptr<std::string>> IDPointerMap::id2pointer;

int main () {
    std::string x = "asdfasf";
    std::shared_ptr<std::string> ptr = IDPointerMap::getPointer(x);
    std::shared_ptr<std::string> ptr2 = IDPointerMap::getPointer(x);
    std::unordered_set<std::shared_ptr<std::string>> ps;
    ps.insert(ptr);
    ps.insert(ptr2);
    std::weak_ptr<std::string> y = ptr;
    ps.erase(y);
    std::cout << ps.size() << std::endl;
    if (ptr) {
        std::cout << *ptr << "\t" << ptr.use_count() << std::endl;
    } else {
        std::cout << "ptr is expired" << std::endl;
    }
    IDPointerMap::erase(x);
    if (ptr2) {
        std::cout << *ptr2 << "\t" << ptr2.use_count() << std::endl;
    } else {
        std::cout << "ptr is expired" << std::endl;
    }
    ps.erase(ptr);
    if (ptr2) {
        std::cout << *ptr2 << "\t" << ptr2.use_count() << std::endl;
    } else {
        std::cout << "ptr is expired" << std::endl;
    }
    return 0;
}