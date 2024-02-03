#include <iostream>
#include <thread>
#include <ctime>

void test_clock_t() {
    // clock()计算从程序启动到到调用该函数所占用的cpu时间，单位为ms
    // 别用该方法进行计时
    clock_t start = clock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    clock_t end = clock();
    std::cout << "clock_t time: " << end - start << "ms" << std::endl;
}

void test_time_t() {
    // time()返回当前时间到起点时间的时间差，单位为s
    time_t start = time(nullptr);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    time_t end = time(nullptr);
    std::cout << "time_t time: " << end - start << "s" << std::endl;
}

int main() {
    test_clock_t();
    test_time_t();
    return 0;
}