#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;
using namespace chrono;

int main() {
    atomic<bool> done(false);
    atomic<unsigned long long> counter(0);
    thread counting([&]() {
        while (!done) ++counter;
    });
    cout << "Kernel-thread demonstration: counting continues while main thread waits.\n";
    this_thread::sleep_for(milliseconds(1000));
    done = true;
    counting.join();
    cout << "Counter increments while main thread is waiting: " << counter << "\n";
    cout << "In a cooperative user-level model, a blocking operation can stop the only carrier thread.\n";
    cout << "This Windows version demonstrates the kernel-thread side safely without blocking on console input.\n";
    return 0;
}
