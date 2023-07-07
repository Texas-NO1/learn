#include <iostream>
#include <vector>

class Heap : public std::vector<int> {
public:
    Heap() {};
    Heap(std::initializer_list<value_type> l) : std::vector<value_type>(l) {};
    int heap_size = size() - 1;
    int length = size() - 1;
};

inline int left(int i) {
    return i << 1;
}

inline int right(int i) {
    return (i << 1) + 1;
}

inline int parent(int i) {
    return i >> 1;
}

// A[0]无意义，从1开始
void max_heapify(Heap &A, int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l <= A.heap_size && A[l] > A[largest]) largest = l;
    if (r <= A.heap_size && A[r] > A[largest]) largest = r;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        // std::cout << "swap " << A[i] << "," << A[largest] << std::endl;
        max_heapify(A, largest);
    }
}

// A[0]无意义，从1开始
void max_heapify_loop(Heap &A, int i) {
    while (true) {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l <= A.heap_size && A[l] > A[largest]) largest = l;
        if (r <= A.heap_size && A[r] > A[largest]) largest = r;
        if (largest != i) {
            std::swap(A[i], A[largest]);
            // std::cout << "swap " << A[i] << "," << A[largest] << std::endl;
            i = largest;
        } else {
            break;
        }
    }
}

void build_max_heap(Heap &A) {
    for (int i = A.heap_size / 2; i >= 1; --i) {
        max_heapify_loop(A, i);
    }
}

void heapsort(Heap &A) {
    build_max_heap(A);
    for (int i = A.length; i >= 2; --i) {
        std::swap(A[i], A[1]);
        A.heap_size--;
        std::cout << "swap (" << 1 << "," << i << ") " << A[i] << "," << A[1] << std::endl;
        max_heapify_loop(A, 1);
    }
}


int heap_maximum(Heap &A) {
    return A[1];
}

int heap_extract_maximum(Heap &A) {
    if (A.heap_size < 1) std::cout << "heap underflow\n";
    int max = A[1];
    A[1] = A[A.heap_size];
    A.heap_size--;
    max_heapify_loop(A, 1);
    return max;
}

void heap_increase_key(Heap &A, int i, int key) {
    if (key < A[i]) 
        std::cout << "new key is smaller than current key\n";
    A[i] = key;
    while (i > 1 && parent(i) < key) {
        std::swap(A[parent(i)], A[i]);
        i = parent(i);
    }
}

void heap_increase_key_update(Heap &A, int i, int key) {  // 正确
    if (key < A[i]) 
        std::cout << "new key is smaller than current key\n";
    A[i] = key;
    while (i > 1 && A[parent(i)] < key) { // 根到叶子节点是有序数组，可以用插入排序的逻辑
        A[i] = A[parent(i)];
        i = parent(i);
    }
    A[i] = key;
}

void max_heap_insert(Heap &A, int key) {
    A.heap_size += 1;
    A[A.heap_size] = INT32_MIN;
    heap_increase_key(A, A.heap_size, key);
}

void heap_delete(Heap &A, int i) {
    A[i] = A[A.heap_size];
    max_heapify_loop(A, i);
}


int main () {
    // int n = 100;
    Heap vec = {0, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    Heap vec2 = vec;
    Heap vec3 = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    Heap vec4 = vec3;
    max_heapify(vec, 2);
    for (auto &v : vec) std::cout << v << " ";
    std::cout << std::endl;

    max_heapify_loop(vec2, 2);
    for (auto &v : vec2) std::cout << v << " ";
    std::cout << std::endl;

    build_max_heap(vec3);
    for (auto &v : vec3) std::cout << v << " ";
    std::cout << std::endl;

    heapsort(vec4);
    for (auto &v : vec4) std::cout << v << " ";
    std::cout << std::endl;
    return 0;
}