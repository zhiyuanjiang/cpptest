#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>


std::shared_mutex mu;
std::mutex tm;
int count = 0;

void tread() {
    std::shared_lock<std::shared_mutex> lock(mu);
    for(int i = 0; i < 5; ++i){
        {
            std::unique_lock<std::mutex> l(tm);
            std::cout << "count:" << count << " id:" << std::this_thread::get_id() << std::endl;
        }        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void tadd() {
    std::unique_lock<std::shared_mutex> lock(mu);
    count++;
    std::cout << "add count: " << count << std::endl;
}

int main() {

    std::thread t1(tread);
    std::thread t2(tread);
    std::thread t3(tadd);
    std::thread t4(tread);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
