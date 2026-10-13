#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

queue<function<void()> > tasks;
mutex queue_mtx;
condition_variable cv;
bool stop = false;

void worker(int id) {
    while (true) {
        function<void()> task;

        {
            unique_lock<mutex> lock(queue_mtx);
            cv.wait(lock, [] { return stop || !tasks.empty(); });

            if (stop && tasks.empty())
                return;

            task = move(tasks.front());
            tasks.pop();
        }

        cout << "Worker " << id << " executing a task." << endl;
        task();
    }
}

void add_task(function<void()> task) {
    {
        lock_guard<mutex> lock(queue_mtx);
        tasks.push(move(task));
    }
    cv.notify_one();
}

int main() {
    vector<thread> workers;
    for (int i = 1; i <= 3; ++i)
        workers.push_back(thread(worker, i));

    for (int i = 1; i <= 6; ++i) {
        add_task([i] {
            cout << "Task " << i << " completed." << endl;
        });
    }

    this_thread::sleep_for(chrono::milliseconds(500));

    {
        lock_guard<mutex> lock(queue_mtx);
        stop = true;
    }
    cv.notify_all();

    for (size_t i = 0; i < workers.size(); ++i)
        workers[i].join();

    cout << "Worker thread pool stopped." << endl;
    return 0;
}