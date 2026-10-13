#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

/* Dev-C++ installations may not support C++20 std::jthread.
   This program demonstrates the same automatic-join idea using std::thread. */

class AutoJoinThread {
    thread t;
public:
    template<class F>
    AutoJoinThread(F f) : t(f) {}
    ~AutoJoinThread() {
        if (t.joinable()) t.join();
    }
};

void worker_fn() {
    cout << "Worker is executing." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Worker finished." << endl;
}

int main() {
    {
        AutoJoinThread jt(worker_fn);
        cout << "Thread created inside scope." << endl;
    }
    cout << "Scope ended; worker was joined automatically." << endl;
    return 0;
}