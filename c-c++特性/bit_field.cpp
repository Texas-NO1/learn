#include <iostream>
#include <memory>
#include <string>
#include <cstring>

struct BitField {
    uint32_t i1 : 1; // 类型占32位，最终占用1位，先开辟32位
    uint16_t i2 : 1; // 类型占16位，最终占用1位，前面开辟了32位，但只占用了1位，故跟在前面
    uint32_t i3 : 1; // 类型占32位，最终占用1位，前面开辟了32位，但只占用了2位，故跟在前面
    uint64_t i4 : 1; // 类型占64位，最终占用1位，前面开辟了32位，但只占用了3位，由于自身类型需要64位，故前面都放在自己的前半段（前三位），自己则从第4位开始使用
    uint64_t i5 : 1; // 类型占64位，最终占用1位，前面开辟了64位，但只占用了4位，故跟在前面
    uint64_t : 3; // 类型占64位，最终占用3位，前面开辟了64位，但只占用了5位，故跟在前面，即跳过这三位开始下一字节
    uint64_t i6 : 1; // 类型占64位，最终占用1位，前面开辟了64位，但只占用了8位，故跟在前面
    unsigned i7 : 1;
}; // 8字节，即uint64_t的大小

int main () {
    std::cout << "size : " << sizeof(BitField) << std::endl;
    uint64_t tmp = 0;
    {
        tmp = 0;
        BitField *b = (BitField*)&tmp;
        b->i1 = 1;
        std::cout << "i1 " << tmp << std::endl; // 1，与机器大小端相关，由于是小端模式，地址低处放数字低位，（内存地址0x00000000，设分别为0xABCD，则A是最前面的地址，存放的是数字低位），即A=0x01，00000001
    }
    {
        tmp = 0;
        BitField *b = (BitField*)&tmp;
        b->i2 = 1;
        std::cout << "i2 " << tmp << std::endl; // 2，即A=0x02，00000010
    }
    {
        tmp = 0;
        BitField *b = (BitField*)&tmp;
        b->i3 = 1;
        std::cout << "i3 " << tmp << std::endl; // 4，即A=0x04，00000100
    }
    {
        tmp = 0;
        BitField *b = (BitField*)&tmp;
        b->i4 = 1;
        std::cout << "i4 " << tmp << std::endl; // 8，即A=0x08，00001000
    }
    {
        tmp = 0;
        BitField *b = (BitField*)&tmp;
        b->i5 = 1;
        std::cout << "i5 " << tmp << std::endl; // 16，即A=0x10，00010000
    }
    // 跳过3位
    {
        tmp = 0;
        BitField *b = (BitField*)&tmp;
        b->i6 = 1;
        std::cout << "skip 3bit, i6 " << tmp << std::endl; // 256，即A=0x00，00000000; B=0x01，00000001
    }
    {
        tmp = 0;
        BitField *b = (BitField*)&tmp;
        b->i7 = 1;
        std::cout << "i7 " << tmp << std::endl; // 512，即A=0x00，00000000; B=0x02，00000010
    }
    return 0;
}