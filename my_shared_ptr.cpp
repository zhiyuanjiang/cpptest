#include <iostream>

/*
shared_ptr 实现
1. 需要一个指针来指向 裸指针
2. 需要一个指针来记录 引用计数 （不能使用常数，因为多个shared_ptr需要更新同一个 计数）
3. 普通构造函数
4. 拷贝构造函数 和 赋值构造函数
5. 析构函数
*/

template<class T>
class MySharedPtr {
public:
    MySharedPtr(T* ptr = nullptr) : ptr_(ptr), count_(ptr ? new size_t(1) : nullptr) {}

    MySharedPtr(const MySharedPtr& rhs) : ptr_(rhs.ptr_), count_(rhs.count_) {
        std::cout << "拷贝构造函数" << std::endl;
        (*count_)++;
    }

    MySharedPtr& operator=(const MySharedPtr& rhs) {
        std::cout << "拷贝赋值函数" << std::endl;
        if (this != &rhs) {
            // 释放当前智能指针指向的对象
            release();
            ptr_ = rhs.ptr_;
            count_ = rhs.count_;
            (*count_)++;
        }
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }
    size_t use_count() const { return *count_; }

    ~MySharedPtr() {
        release();
    }

private:
    void release() {
        if (count_ && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }
    }

    T* ptr_;
    size_t* count_;
};

class MyClass {
public:
    MyClass() { std::cout << "MyClass 构造函数\n"; }
    ~MyClass() { std::cout << "MyClass 析构函数\n"; }
    void do_something() { std::cout << "MyClass::do_something() 被调用\n"; }
};


int main() {

    {
        MySharedPtr<MyClass> ptr1(new MyClass());
        MySharedPtr<MyClass> ptr2(new MyClass());
        {
            ptr2 = ptr1;
            ptr1->do_something();
            ptr2->do_something();
            std::cout << "引用计数: " << ptr1.use_count() << std::endl;
        }
        std::cout << "引用计数: " << ptr1.use_count() << std::endl;
    }

    return 0;
}