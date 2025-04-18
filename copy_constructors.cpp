#include <iostream>

/*
拷贝构造函数（copy constructors） & 拷贝赋值函数 （copy assignment operator）
拷贝构造函数形式:
MyClass(const MyClass&)
拷贝赋值函数的形式:
MyClass& operator=(const MyClass&)
*/

class MyClass {
public:
    MyClass() {
        std::cout << "普通构造函数" << std::endl;
    }

    MyClass(const MyClass&) {
        std::cout << "拷贝构造函数" << std::endl;
    }

    MyClass& operator=(const MyClass& rhs) {
        std::cout << "拷贝赋值函数" << std::endl;
        if (this != &rhs) {
            // 释放原有的资源
            // ...
            // 分配新资源，拷贝内容
            // ...
        }
        return *this;
    }
};

int main() {

    MyClass t1;
    MyClass t2(t1);
    MyClass t3 = t2;
    t1 = t3;
    return 0;
}