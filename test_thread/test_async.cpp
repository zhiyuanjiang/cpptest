#include <iostream>
#include <future>
#include <thread>

int test1() {
    std::cout << "test1, pid: " << std::this_thread::get_id() << std::endl;
    return 2;
}

void test2() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "test2, pid: " << std::this_thread::get_id() << std::endl;
}

int main() {
    // std::future<int> the_answer = std::async(std::launch::deferred, find_the_answer_to_ltuae);
    std::future<int> the_answer = std::async(std::launch::async, test1);
    test2();
    std::cout << "the answer is: " << the_answer.get() << std::endl;

    return 0;
}
