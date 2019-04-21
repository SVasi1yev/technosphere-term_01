#include <thread>
#include <iostream>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <mutex>
#include <condition_variable>

#define REQ_TIMES 1000000

// std::mutex lock;
// std::condition_variable cv1, cv2;
// bool b1, b2;

void threadPing(std::atomic<int>& a) {
    while(a < REQ_TIMES) {
        if(a % 2 == 0) {
            std::cout << "ping\n";
            a++; 
        }
    }
}
void threadPong(std::atomic<int>& a) {
    while(a < REQ_TIMES) {
        if(a % 2 == 1) {
            std::cout <<"pong\n";
            a++;
        }
    }
}

// void threadPing() {
//     std::cout << "ping\n";
//     b2 = true;
//     cv2.notify_one();
//     for (int i = 1; i < REQ_TIMES; i++) {
//         std::unique_lock<std::mutex> locker(lock);
//         while(!b1)
//             cv1.wait(locker);
//         std::cout << "ping\n";
//         b1 = false;
//         b2 = true;
//         cv2.notify_one();
//     }
// }
// void threadPong() {
//     for (int i = 0; i < REQ_TIMES; i++) {
//         std::unique_lock<std::mutex> locker(lock);
//         while(!b2)
//             cv2.wait(locker);
//         std::cout << "pong\n";
//         b2 = false;
//         b1 = true;
//         cv1.notify_one();
//     }
// }

int main (int argc, char* argv[]) {
    // auto q1 = std::chrono::system_clock::now();
    
    std::atomic<int> a(0);
    std::thread t1(threadPing, std::ref(a));
    std::thread t2(threadPong, std::ref(a));

    // std::thread t1(threadPing);
    // std::thread t2(threadPong);

    t1.join();
    t2.join();

    // auto q2 = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds = q2-q1;
    // std::cout << elapsed_seconds.count() << '\n';

    return 0;
}