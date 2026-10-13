#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtxA, mtxB;

void thread1() {
    lock_guard<mutex> lockA(mtxA);
    cout << "Thread 1 acquired Lock A." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Thread 1 is waiting for Lock B." << endl;
    lock_guard<mutex> lockB(mtxB);
    cout << "Thread 1 acquired Lock B." << endl;
}

void thread2() {
    lock_guard<mutex> lockB(mtxB);
    cout << "Thread 2 acquired Lock B." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Thread 2 is waiting for Lock A." << endl;
    lock_guard<mutex> lockA(mtxA);
    cout << "Thread 2 acquired Lock A." << endl;
}

int main() {
    cout << "Deadlock simulation started." << endl;
    cout << "WARNING: The two threads can wait forever." << endl;

    thread t1(thread1);
    thread t2(thread2);

    // Do not join because this demonstration intentionally deadlocks.
    t1.detach();
    t2.detach();

    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Circular wait demonstrated: T1 waits for B, T2 waits for A." << endl;
    return 0;
}