#include <iostream>
#include <type_traits>

void func() {
    std::cout << "test" << std::endl;
}
typedef void (*fptr)();

void decltype_function_type() {
    std::cout << "func type is void(): " << std::is_same_v<decltype(func), void()> << std::endl;
}

void decay_function_pointer() {
    std::cout << "decay func type is void(*)(): " << std::is_same_v<std::decay_t<decltype(func)>, void(*)()> << std::endl;
}

int main() {
    fptr tmp = &func;
    tmp();   
    decltype_function_type();
    decay_function_pointer();
}