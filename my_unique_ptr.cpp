#include <iostream>
#include <utility>

/*
unique_ptr实现：
1. 需要一个指针来指向 裸指针
2. 普通构造函数 
3. 拷贝构造函数 和 赋值构造函数 需要被禁用 （只能有一个unique_ptr指向对象）
4. 移动拷贝构造函数 和 移动赋值构造函数
5. 析构函数
*/

template<class T>
class MyUniquePtr {
public:
    MyUniquePtr(T* ptr) : ptr_(ptr) {
        std::cout << "构造函数" << std::endl;
    }

    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;

    MyUniquePtr(MyUniquePtr&& rhs) : ptr_(rhs.ptr_) {
        std::cout << "移动拷贝构造函数" << std::endl;
        rhs.ptr_ = nullptr;
    }
    MyUniquePtr& operator=(MyUniquePtr&& rhs) {
        std::cout << "移动赋值构造函数" << std::endl;
        if (this != &rhs) {
            release();
            ptr_ = rhs.ptr_;
            rhs.ptr_ = nullptr;
        }
        return *this;
    }

    ~MyUniquePtr() {
        release();
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }

private:
    T* ptr_;

    void release() {
        if (ptr_) {
            delete ptr_;
            ptr_ = nullptr;
        }
    }
};

int main() {

    MyUniquePtr<int> p1(new int(5));
    MyUniquePtr<int> p2(new int(2));
    MyUniquePtr<int> p3(std::move(p2));
    p1 = std::move(p3);

    return 0;
}
