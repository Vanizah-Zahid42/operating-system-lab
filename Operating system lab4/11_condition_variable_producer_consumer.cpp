#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

queue<int> q;
mutex mtx;
condition_variable cv;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            lock_guard<mutex> lock(mtx);
            q.push(i);
            cout << "Producer added: " << i << endl;
        }
        cv.notify_one();
    }
}

void consumer() {
    for (int i = 1; i <= 5; ++i) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !q.empty(); });

        int item = q.front();
        q.pop();
        cout << "Consumer removed: " << item << endl;
    }
}

int main() {
    thread p(producer);
    thread c(consumer);

    p.join();
    c.join();

    cout << "Producer-Consumer completed." << endl;
    return 0;
}