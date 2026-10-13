#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

class Barrier {
    mutex m;
    condition_variable cv;
    int count, waiting, generation;
public:
    Barrier(int n) : count(n), waiting(0), generation(0) {}

    void arrive_and_wait() {
        unique_lock<mutex> lock(m);
        int gen = generation;
        ++waiting;

        if (waiting == count) {
            waiting = 0;
            ++generation;
            cv.notify_all();
        } else {
            cv.wait(lock, [this, gen] { return gen != generation; });
        }
    }
};

Barrier sync_point(3);

void worker(int id) {
    cout << "Worker " << id << " completed Phase 1." << endl;
    sync_point.arrive_and_wait();

    cout << "Worker " << id << " started Phase 2." << endl;
}

int main() {
    vector<thread> workers;
    for (int i = 1; i <= 3; ++i)
        workers.push_back(thread(worker, i));

    for (size_t i = 0; i < workers.size(); ++i)
        workers[i].join();

    cout << "All workers completed both phases." << endl;
    return 0;
}