#include <iostream>
#include <thread>
#include <future>

std::promise<int> promise;
std::future<int> future = promise.get_future();

void test(std::promise<int> promise) {
    promise.set_value(2);
}

int test2() {
    return 1;
}

int main() {

    std::thread t(test, std::move(promise));
    std::cout << "value: " << future.get() << std::endl;
    t.join();

    std::packaged_task<int()> task(test2);
    std::future<int> f = task.get_future();
    std::thread t2(std::move(task));
    std::cout << "value: " << f.get() << std::endl;
    t2.join();

    return 0;
}
