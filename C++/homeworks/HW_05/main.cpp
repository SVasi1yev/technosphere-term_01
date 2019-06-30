#include <thread>
#include <iostream>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <mutex>
#include <condition_variable>

const int req_times = 1e6;

void threadPing(std::atomic<int>& a) {
    while(a < req_times) {
        if(a % 2 == 0) {
            std::cout << "ping\n";
            a++; 
        }
    }
}
void threadPong(std::atomic<int>& a) {
    while(a < req_times) {
        if(a % 2 == 1) {
            std::cout <<"pong\n";
            a++;
        }
    }
}

int main (int argc, char* argv[]) {
    std::atomic<int> a(0);

    std::thread t1(threadPing, std::ref(a));
    std::thread t2(threadPong, std::ref(a));

    t1.join();
    t2.join();

    return 0;
}