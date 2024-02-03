#include <iostream>
#include <ctime>

void test_ctime() {
    time_t time = std::time(nullptr);
    char* pt = std::ctime(&time);
    std::cout << "time_t format: " << pt << std::endl;
}

void test_localtime() {
    time_t time = std::time(nullptr);
    tm* fmt = std::localtime(&time);
    std::cout << "time_t format: " << fmt->tm_year + 1900 << " " << fmt->tm_mon + 1 << " " << fmt->tm_mday << std::endl; 
}

int main() {
    test_ctime();
    test_localtime();
    return 0;
}