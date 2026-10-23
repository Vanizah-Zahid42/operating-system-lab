#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

int main() {
    const int capacity = 5, total = 20;
    queue<int> buffer;
    mutex m;
    condition_variable notFull, notEmpty;
    thread producer([&]() {
        for (int i = 1; i <= total; ++i) {
            unique_lock<mutex> lock(m);
            notFull.wait(lock, [&]() { return (int)buffer.size() < capacity; });
            buffer.push(i);
            cout << "Produced: " << i << "\n";
            lock.unlock();
            notEmpty.notify_one();
        }
        unique_lock<mutex> lock(m);
        notFull.wait(lock, [&]() { return (int)buffer.size() < capacity; });
        buffer.push(-1);
        lock.unlock();
        notEmpty.notify_one();
    });
    thread consumer([&]() {
        while (true) {
            unique_lock<mutex> lock(m);
            notEmpty.wait(lock, [&]() { return !buffer.empty(); });
            int x = buffer.front();
            buffer.pop();
            lock.unlock();
            notFull.notify_one();
            if (x == -1) break;
            cout << "Consumed: " << x << "\n";
        }
    });
    producer.join();
    consumer.join();
    return 0;
}
