#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

bool ready{false}; 
std::mutex mu;
std::condition_variable cond;

void run() {
    std::unique_lock<std::mutex> lock(mu);
    cond.wait(lock, []{ 
        std::cout << "check" << std::endl;
        return ready; 
    });
    std::cout << "run end" << std::endl;
}

int main() {

    std::thread t1(&run);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::unique_lock<std::mutex> lock(mu);
        ready = true;
    }   
    cond.notify_one();
    std::cout << "ok" << std::endl;
    t1.join();
    return 0;
}