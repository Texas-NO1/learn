#include <iostream>
#include <cstring>

// 自己实现string

class String {
private:
    int length;
    int capacity;
    char *data;
    void check_expend_capacity(int add_cnt) {
        if (length + add_cnt > capacity) {
            capacity = std::max(capacity * 2, length + add_cnt);
            /* 进阶方法：定位new，直接在原来的地址上申请增大内存 */
            new (data) char[capacity];
            /*
            朴素方法：申请一块更大的内存，将当前数据copy过去
            char *temp = new char[capacity];
            strcpy(temp, data);
            delete [] data;
            data = temp;
            */
        }
    }
public:
    String() : length(0), data(nullptr) {}
    String(const char *str) {
        capacity = length = strlen(str);
        data = new char[length];
        strcpy(data, str);
    }
    void push_back(char c) {
        check_expend_capacity(1);
        data[length++] = c;
    }
    char& operator[] (int idx) {
        return data[idx];
    }
    char& operator[] (int idx) const {
        return data[idx];
    }
    String& operator+(const String &str) {
        check_expend_capacity(str.size());
        for (int i = 0; i < str.size(); ++i) {
            data[length++] = str[i];
        }
        return *this;
    }
    friend std::ostream& operator << (std::ostream &out, const String &str) {
        out << str.data;
        return out;
    }
    int size() const {
        return length;
    }
    ~String() {
        if (data != nullptr) delete [] data;
    }
};

int main () {
    String str = "12345";
    std::cout << str << std::endl;
    std::cout << str.size() << std::endl;
    str = str + "67890";
    std::cout << str << std::endl;
    std::cout << str.size() << std::endl;
    // std::cout << xxx; 实际上调用的是operator<<(std::cout, xxx)
    // 因此重载operator<<的参数是cout和具体类型对象，
    operator<<(std::cout, "xxx");
    return 0;
}