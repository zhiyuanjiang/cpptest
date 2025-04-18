#include <iostream>
#include <assert.h>

/*
对象池
1. 内存分配, 构造对象
2. 析构对象, 内存回收
3. operator new 和 placement new 
*/

template<class T>
class ObjPool {
public:
    explicit ObjPool(size_t n) : free_list(nullptr) {
        char* start_addr = (char*)::operator new(n * sizeof(T));   // 返回一个void*指针
        pool_start = start_addr;
        for (size_t i = 0; i < n; ++i) {
            obj* alloc_obj = (obj*)start_addr;
            std::cout << "addr: " << (void*)start_addr << std::endl;
            alloc_obj->free_next = free_list;
            free_list = alloc_obj;
            start_addr += sizeof(T);
        }
    }

    template<class... Args>
    T* construct(Args&&... args) {
        char* addr = alloc();
        assert(addr != nullptr);
        return new (addr) T(args...);
    }

    void destruct(T* t) {
        t->~T();
        destroy(t);
    }

    ~ObjPool() {
        ::operator delete(pool_start);
    }
    

private:
    char* alloc() {
        if (free_list) {
            char* addr = free_list->user_data;
            free_list = free_list->free_next;
            std::cout << "alloc addr: " << (void*)addr << std::endl;
            return addr;
        }
        return nullptr;
    }

    void destroy(T* t) {
        obj* alloc_obj = (obj*)t;
        alloc_obj->free_next = free_list;
        free_list = alloc_obj;
        std::cout << "free addr: " << (void*)free_list->user_data << std::endl;
    }

    union obj {
        obj* free_next;
        char user_data[1];
    };
    obj* free_list;
    char* pool_start;
};

class MyClass {
public:
    MyClass() {
        std::cout << "construct my class" << std::endl;
    }
    MyClass(int t) : t(t) {
        std::cout << "construct t = " << t << std::endl;
    }
    ~MyClass() {
        std::cout << "destruct my class" << std::endl;
    }
    int t = 0;
};

int main() {

    ObjPool<MyClass> my_class_pool(10);
    MyClass* t1 = my_class_pool.construct();
    MyClass* t2 = my_class_pool.construct();
    my_class_pool.destruct(t1);
    my_class_pool.destruct(t2);

    MyClass* t3 = my_class_pool.construct<int>(2);
    my_class_pool.destruct(t3);

    return 0;
}