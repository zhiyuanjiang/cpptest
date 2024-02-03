#include <iostream>
#include <memory>

/*
*   这个例子中，当A，B内部使用的是shared_ptr时，会发生循环引用的问题，到时A，B的资源得不到释放，
*   造成内存泄漏。我们以对象A为例分析，对象A在堆上new了内存，所以当变量a释放时，对象A不会被自动释放，
*   这个时候资源的释放依赖于智能指针，当指针计数为0，则释放内存。然后对象B内部有一个指针指向了A，
*   由于B对象不会被释放，导致了A对象的智能指针计数不会归0，A对象不会被释放。同理，由于A对象不会
*   被释放，导致B对象也不会被释放，这就是循环引用。
*/ 

class B;

class A {
public:
    A() = default;
    ~A() {
        std::cout << "destruct A" << std::endl;
    }
    // std::shared_ptr<B> _ptr = nullptr;
    std::weak_ptr<B> _ptr;
};

class B {
public:
    B() = default;
    ~B() {
        std::cout << "destruct B" << std::endl;
    }
    // std::shared_ptr<A> _ptr = nullptr; 
    std::weak_ptr<A> _ptr;
};

int main() {

    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    std::cout << "A use count: " << a.use_count() << std::endl;
    std::cout << "B use count: " << b.use_count() << std::endl;
    a->_ptr = b;
    b->_ptr = a;
    std::cout << "A use count: " << a.use_count() << std::endl;
    std::cout << "B use count: " << b.use_count() << std::endl;
    return 0;
}