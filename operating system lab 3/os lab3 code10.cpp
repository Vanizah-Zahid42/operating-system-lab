#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
int main() {
    queue<int> buffer;
    const size_t CAPACITY = 3;
    mutex mtx;
    condition_variable cvProducer, cvConsumer;
    thread producer([&]() {
        for (int item=1; item<=5; ++item) {
            unique_lock<mutex> lock(mtx);
            cvProducer.wait(lock, [&]() { return buffer.size() < CAPACITY; });
            buffer.push(item);
            cout << "Produced: " << item << endl;
            lock.unlock();
            cvConsumer.notify_one();
        }
    });
    thread consumer([&]() {
        for (int i=0; i<5; ++i) {
            unique_lock<mutex> lock(mtx);
            cvConsumer.wait(lock, [&]() { return !buffer.empty(); });
            int item=buffer.front(); buffer.pop();
            cout << "Consumed: " << item << endl;
            lock.unlock();
            cvProducer.notify_one();
        }
    });
    producer.join(); consumer.join();
}
