#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

class Latch {
    mutex m;
    condition_variable cv;
    int count;
public:
    Latch(int n) : count(n) {}

    void wait() {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this] { return count == 0; });
    }

    void count_down() {
        {
            lock_guard<mutex> lock(m);
            if (count > 0) --count;
        }
        cv.notify_all();
    }
};

Latch start_flag(1);

void worker(int id) {
    cout << "Worker " << id << " waiting for start signal." << endl;
    start_flag.wait();
    cout << "Worker " << id << " running benchmark." << endl;
}

int main() {
    vector<thread> workers;
    for (int i = 1; i <= 3; ++i)
        workers.push_back(thread(worker, i));

    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Main: shared memory prepared. Releasing workers." << endl;
    start_flag.count_down();

    for (size_t i = 0; i < workers.size(); ++i)
        workers[i].join();

    cout << "All workers completed." << endl;
    return 0;
}