#include <vector>
#include <set>
#include <unordered_set>
#include <string>
#include <map>
#include <unordered_map>
#include <stdlib.h>

template <typename T>
void showSTLSize() {
    printf("str %d\n", sizeof(std::string));
    printf("vec %d\n", sizeof(std::vector<T>));
    printf("set %d\n", sizeof(std::set<T>));
    printf("map %d\n", sizeof(std::map<T, T>));
    printf("unordered_set %d\n", sizeof(std::unordered_set<T>));
    printf("unordered_map %d\n", sizeof(std::unordered_map<T, T>));
}

void showStringItemSize0() {
    std::string str; // use localbuf
}
void showStringItemSize16() {
    std::string str("xxxxxxxxxxxxxxx"); // use localbuf
}
void showStringItemSize17() {
    std::string str("xxxxxxxxxxxxxxxx"); // new 17
}

void showVectorItemSize() {
    std::vector<int> vec(1);
}

void showSetMapItemSize() {
    std::set<uint64_t> s;
    s.insert(1);
    // s.insert(2);
    // s.insert(3);
    // printf("%d\n", sizeof(std::_Rb_tree_key_compare<uint64_t>));
}

void showUnorderedSetUnorderedMapSize() {
    /**
     * @brief       __bucket_type*		_M_buckets		= &_M_single_bucket;
      size_type			_M_bucket_count		= 1;
      __node_base		_M_before_begin;
      size_type			_M_element_count	= 0;
      _RehashPolicy		_M_rehash_policy;

      // A single bucket used when only need for 1 bucket. Especially
      // interesting in move semantic to leave hashtable with only 1 buckets
      // which is not allocated so that we can have those operations noexcept
      // qualified.
      // Note that we can't leave hashtable with 0 bucket without adding
      // numerous checks in the code to avoid 0 modulus.
      __bucket_type		_M_single_bucket	= nullptr;
     * 
     */
    std::unordered_set<uint64_t> s;
    printf("h table %d\n", sizeof(std::__uset_hashtable<uint64_t>));
    // printf("bucket %d\n", s.bucket_count());
    // printf("max bucket %d\n", s.max_bucket_count());
    s.insert(1);
    // s.insert(2);
    // s.insert(3);
    // s.insert(4);
    // s.insert(5);
    // s.insert(6);
    // s.insert(7);
    // s.insert(8);
    // s.insert(9);
    // s.insert(10);
    // s.insert(11);
    // s.insert(12);
    // s.insert(13); // 质数，hash因子，rehash大小
    // s.insert(14); // 开始rehash
    // printf("bucket %d\n", s.bucket_count());
    // for (int i = 0; i < s.bucket_count(); ++i) {
    //     printf("bucket id %d, size %d\n", i, s.bucket_size(i));
    // }
    // printf("factor %f\n", s.load_factor());
    // printf("max factor %f\n", s.max_load_factor());
    // printf("max bucket %d\n", s.max_bucket_count());
}

int main () {
    // showSTLSize<char>();
    // showSTLSize<std::string>();
    // showStringItemSize0();
    // showStringItemSize16();
    // showStringItemSize17();
    // showVectorItemSize();
    // showSetMapItemSize();
    showUnorderedSetUnorderedMapSize();
    return 0;
}