#include <iostream>
#include <sys/time.h>

void test_gettimeofday() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long time_s = tv.tv_sec;
    long time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000.0; // ms
    std::cout << "time: " << time_s << "s" << " " << time_ms << "ms" << std::endl;
}

int main() {
    test_gettimeofday();
    return 0;
}