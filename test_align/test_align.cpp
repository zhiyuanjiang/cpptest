#include <iostream>

/*
*   alignof操作符 返回类型的内存对齐值 std::size_t
*
*   alignas关键字 指定类型的内存对齐值，需要满足两个条件：
*   1 对齐值 > alignof(type)
*   2 对齐值 = pow(2, n)
*
*   std::aligned_storage
*   template<std::size_t Len, std::size_t Align>
*   struct aligned_storage;
*/

struct Foo {
    char c;
    int i1;
    int i2;
    long l;
};

struct alignas(4) Too {
    char c;
    int i1;
    int i2;
    long l;
};

#define show_size_and_align(type) \
    std::cout << "size:" << sizeof(type) << " align:" << alignof(type) << std::endl;

int main() {

    show_size_and_align(char);
    show_size_and_align(int);
    show_size_and_align(long);
    show_size_and_align(Foo);
    show_size_and_align(Too);

    return 0;
}