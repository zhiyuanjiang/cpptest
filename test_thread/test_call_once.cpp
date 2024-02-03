#include <iostream>
#include <thread>
#include <mutex>

std::once_flag test_flag;

void print() {
    std::call_once(test_flag, []{
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "just print once" << std::endl;
    });
    std::cout << "id:" << std::this_thread::get_id() << " end" << std::endl;
}

int main() {

    std::thread t1(print);
    std::thread t2(print);
    std::thread t3(print);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}