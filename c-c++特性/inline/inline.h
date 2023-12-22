class InlineTest {
public:
    void nonInlineTest();
    void inlineTest();
};

// inline方法必须在同一个文件内声明定义
inline void InlineTest::inlineTest() {
    std::cout << "inline" << std::endl;
}