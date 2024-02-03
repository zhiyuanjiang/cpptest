#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

void test_system_clock_format() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    // 格式化打印当前时间
    ss << std::put_time(std::localtime(&now_t), "%Y%m%d-%H%M%S");
    std::cout << "system clock format time: " << ss.str() << std::endl;
}

int main() {
    test_system_clock_format();
    return 0;
}