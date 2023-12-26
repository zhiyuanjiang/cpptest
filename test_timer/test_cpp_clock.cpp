/*
*   steady_clock: 单调时钟，只会增长，适合用于记录程序耗时
*   system_clock: 系统时钟，由于系统时钟可以修改，用系统时间计算时间差可能不准
*   high_resolution_clock: 当前系统能提供的最高精度的时钟，不能修改，相当于steady_clock的高精度版本
*/

#include <iostream>
#include <chrono>
#include <thread>

#define TIMESTART(tag) auto tag##_start = std::chrono::steady_clock::now(), tag##_end = tag##_start;
#define TIMEEND(tag) tag##_end = std::chrono::steady_clock::now();
#define DURATION_S(tag) std::cout << #tag << " cost: " << std::chrono::duration_cast<std::chrono::seconds>(tag##_end - tag##_start).count(); 

void test_system_clock() {
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::cout << "system clock gap: " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;
}

void test_steady_clock() {
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    auto end = std::chrono::steady_clock::now();
    std::cout << "steady_clock gap: " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;
}

void test_high_resolution_clock() {
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "high resolution clock gap: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;
}

void test_clock_macro() {
    TIMESTART(test)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    TIMEEND(test)
    DURATION_S(test)
}

int main() {
    test_system_clock();
    test_steady_clock();
    test_high_resolution_clock();
    test_clock_macro();
    return 0;
}