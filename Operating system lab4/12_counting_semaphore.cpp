#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

/* Counting semaphore implementation for older Dev-C++ compilers. */
class Semaphore {
    mutex m;
    condition_variable cv;
    int permits;
public:
    Semaphore(int n) : permits(n) {}

    void acquire() {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this] { return permits > 0; });
        --permits;
    }

    void release() {
        {
            lock_guard<mutex> lock(m);
            ++permits;
        }
        cv.notify_one();
    }
};

Semaphore sem(3);

void task(int id) {
    sem.acquire();
    cout << "Task " << id << " entered the limited resource." << endl;

    this_thread::sleep_for(chrono::milliseconds(300));

    cout << "Task " << id << " finished and released permit." << endl;
    sem.release();
}

int main() {
    vector<thread> threads;
    for (int i = 1; i <= 6; ++i)
        threads.push_back(thread(task, i));

    for (size_t i = 0; i < threads.size(); ++i)
        threads[i].join();

    cout << "All tasks completed. Maximum 3 tasks were allowed at once." << endl;
    return 0;
}