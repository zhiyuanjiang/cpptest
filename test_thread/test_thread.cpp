#include <iostream>
#include <thread>

void print() {
    std::cout << "hello world" << std::endl;
}

int main() {

    std::thread t(print);
    t.join();

    return 0;
}