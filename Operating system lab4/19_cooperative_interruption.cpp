#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

atomic<bool> stop_requested(false);

void worker() {
    int count = 0;

    while (!stop_requested.load()) {
        cout << "Worker doing work: " << ++count << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    cout << "Worker received stop request." << endl;
    cout << "Worker cleaned up resources." << endl;
}

int main() {
    thread t(worker);

    this_thread::sleep_for(chrono::seconds(2));
    cout << "Manager sends stop signal." << endl;
    stop_requested.store(true);

    t.join();

    cout << "Worker terminated safely." << endl;
    return 0;
}