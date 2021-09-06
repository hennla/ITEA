#include <iostream>
#include <thread>
#include <condition_variable>
#include <atomic>

std::condition_variable cv;
std::mutex cv_m;
bool print = false;
bool increment = false;

std::atomic<int> counter{0};

bool interrupted = false;

void produce() {
    counter++;
};

void consume() {
    while (!interrupted) {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, [] { return print; });
        if (counter > 1) std::cout << ", ";
        std::cout << counter;

        print = false;
        increment = true;
        lk.unlock();
        cv.notify_one();
    }
};

int main() {
    int max_repeat = 30;
    std::unique_lock<std::mutex> lk(cv_m);

    std::thread consumer_thread(consume);

    for (int i = 1; i <= max_repeat; i++) {
        if (i == max_repeat) interrupted = true;
        produce();
        print = true;
        increment = false;
        cv.notify_one();
        cv.wait(lk, [] { return increment; });
    }
    consumer_thread.join();
    return 0;
}
